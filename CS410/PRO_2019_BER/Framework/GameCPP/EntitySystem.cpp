#include "EntitySystem.h"

#include <Windows.h>
#include <DbgHelp.h>

namespace GA
{
	bool EntitySystem::create( ga_input_t* pInput, ga_graphics_t* pGraphics )
	{
		m_pInput	= pInput;
		m_pGraphics	= pGraphics;

		return true;
	}

	void EntitySystem::destroy()
	{
		while( !m_entities.empty() )
		{
			destroyEntity( m_entities.begin()->first );
		}

		m_entities.clear();
		m_programs.clear();
		m_components.clear();
	}

	void EntitySystem::registerComponentType( ComponentTypeId id, ComponentCreateFunc createFunc )
	{
		ComponentData& component = m_components[ id ];
		component.id			= id;
		component.createFunc	= createFunc;
	}

	void EntitySystem::unregisterComponentType( ComponentTypeId id )
	{
		m_components.erase( id );
	}

	void EntitySystem::registerProgram( ProgramId id, const EntityProgramComponentBinding* pBindings, size_t bindingCount, EntityProgramUpdateFunc updateFunc )
	{
		ProgramData& program = m_programs[ id ];
		program.id			= id;
		program.bindings.assign( pBindings, pBindings + bindingCount );
		program.updateFunc	= updateFunc;

		buildProgramDependencies();
	}

	void EntitySystem::unregisterProgram( ProgramId id )
	{
		m_programs.erase( id );

		buildProgramDependencies();
	}

	EntityId EntitySystem::createEntity( const EntityCreateComponentData* pComponents, size_t componentCount )
	{
		const EntityId id = m_nextEntityId;
		m_nextEntityId++;

		EntityData& entity = m_entities[ id ];
		entity.id	= id;

		for( size_t i = 0u; i < componentCount; ++i )
		{
			const EntityCreateComponentData& createData = pComponents[ i ];
			const ComponentTypeMap::iterator it = m_components.find( createData.componentId ) ;
			if( it == m_components.end() )
			{
				destroyEntity( id );
			}

			EntityComponent* pComponent	= it->second.createFunc( createData.pInitData );
			pComponent->entityId	= id;
			pComponent->componentId	= createData.componentId;

			entity.components.push_back( pComponent );
		}

		for( ProgramMap::value_type& kvp : m_programs )
		{
			bool hasMatchingComponents = true;
			for( const EntityProgramComponentBinding& binding : kvp.second.bindings )
			{
				bool hasComponent = false;
				for( size_t i = 0u; i < componentCount; ++i )
				{
					hasComponent |= (pComponents[ i ].componentId == binding.componentId);
				}

				hasMatchingComponents &= hasComponent;
			}

			if( hasMatchingComponents )
			{
				kvp.second.updateEntities.insert( id );
			}
		}

		return id;
	}

	void EntitySystem::destroyEntity( EntityId id )
	{
		const EntityMap::iterator it = m_entities.find( id );
		if( it == m_entities.end() )
		{
			return;
		}

		for( EntityComponent* pComponent : it->second.components )
		{
			free( pComponent );
		}

		m_entities.erase( it );
	}

	void EntitySystem::update( double deltaTime )
	{
		EntityUpdateContext context;
		context.deltaTime	= deltaTime;
		context.pInput		= m_pInput;
		context.pGraphics	= m_pGraphics;

		std::vector< EntityProgrammTupleIterator > iterators;
		for( ProgramId systemId : m_programOrder )
		{
			ProgramData& program = m_programs[ systemId ];

			iterators.clear();
			for( const EntityProgramComponentBinding& binding : program.bindings )
			{
				ComponentData& component = m_components[ binding.componentId ];

				EntityProgrammTupleIterator iterator;
				iterator.componentId	= component.id;
				iterator.ioType			= binding.ioType;
				//iterator.pData			= &component.states;

				iterators.push_back( iterator );
			}

			program.updateFunc( context, iterators.data(), iterators.size() );
		}
	}

	//const EntityComponentList* EntitySystem::findComponents( ComponentTypeId id ) const
	//{
	//	const ComponentTypeMap::const_iterator it = m_components.find( id );
	//	if( it == m_components.end() )
	//	{
	//		return nullptr;
	//	}
	//
	//	return &it->second.states;
	//}

	void EntitySystem::buildProgramDependencies()
	{
		m_programOrder.clear();

		ProgramVector remainingSystems;
		std::set< ComponentTypeId > writtenComponents;

		for( const ProgramMap::value_type& kvp : m_programs )
		{
			remainingSystems.push_back( kvp.first );
		}

		bool hasNewSystem = true;
		while( hasNewSystem && !remainingSystems.empty() )
		{
			hasNewSystem = false;

			for( ProgramVector::iterator it = remainingSystems.begin(); it != remainingSystems.end(); ++it )
			{
				const ProgramId systemId = *it;
				const ProgramData& system = m_programs[ systemId ];

				bool requirementsMet = true;
				for( const EntityProgramComponentBinding& binding : system.bindings )
				{
					switch( binding.ioType )
					{
					case EntityProgramIoType::Read:
						requirementsMet &= writtenComponents.find( binding.componentId ) != writtenComponents.end();
						break;

					case EntityProgramIoType::Write:
						break;

					case EntityProgramIoType::ReadWrite:
						break;
					}
				}

				if( !requirementsMet )
				{
					continue;
				}

				m_programOrder.push_back( systemId );
				hasNewSystem = true;

				it = remainingSystems.erase( it );
				if( it == remainingSystems.end() )
				{
					break;
				}
			}
		}

		if( !remainingSystems.empty() )
		{
			OutputDebugStringA( "Failed to build Systems Dependencies.\n" );
			DebugBreak();
		}
	}
}

