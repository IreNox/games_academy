#pragma once

#include "LinkedList.h"

#include <framework.h>
#include <stdint.h>

#include <map>
#include <set>
#include <vector>

namespace GA
{
	using EntityId = uint32_t;
	using ComponentTypeId = uint32_t;
	using ProgramId = uint32_t;

	struct EntityComponent;
	using EntityComponentNode = LinkedListNode< EntityComponent >;

	struct EntityComponent : public EntityComponentNode
	{
		EntityId				entityId;
		ComponentTypeId			componentId;
	};

	using EntityComponentList = LinkedList< EntityComponent >;

	enum class EntityProgramIoType
	{
		Read,
		Write,
		ReadWrite
	};

	struct EntityProgramComponentBinding
	{
		ComponentTypeId			componentId;
		EntityProgramIoType		ioType;
	};

	struct EntityCreateComponentData
	{
		ComponentTypeId			componentId;
		const void*				pInitData;
	};

	struct EntityUpdateContext
	{
		double					deltaTime;
		ga_input_t*				pInput;
		ga_graphics_t*			pGraphics;
	};

	struct EntityProgrammTupleIterator
	{
		ComponentTypeId			componentId;
		EntityProgramIoType		ioType;
		EntityComponentList*	pData;

		EntityComponent*		getFirst();
		EntityComponent*		getNext( EntityComponent* pValue );

		const EntityComponent*	getConstFirst();
		const EntityComponent*	getConstNext( EntityComponent* pValue );
	};

	typedef EntityComponent*(*ComponentCreateFunc)( const void* pInitData );
	typedef void(*EntityProgramUpdateFunc)( const EntityUpdateContext& context, const EntityProgrammTupleIterator* pData, size_t dataCount );

	class EntitySystem
	{
	public:

		bool						create( ga_input_t* pInput, ga_graphics_t* pGraphics );
		void						destroy();

		void						registerComponentType( ComponentTypeId id, ComponentCreateFunc createFunc );
		void						unregisterComponentType( ComponentTypeId id );

		void						registerProgram( ProgramId id, const EntityProgramComponentBinding* pBindings, size_t bindingCount, EntityProgramUpdateFunc updateFunc );
		void						unregisterProgram( ProgramId id );

		EntityId					createEntity( const EntityCreateComponentData* pComponents, size_t componentCount );
		void						destroyEntity( EntityId id );

		void						update( double deltaTime );

		const EntityComponentList*	findComponents( ComponentTypeId id ) const;

	private:

		struct ComponentData
		{
			ComponentTypeId			id;
			ComponentCreateFunc		createFunc;
		};

		struct ProgramData
		{
			using BindingVector = std::vector< EntityProgramComponentBinding >;
			using EntitySet = std::set< EntityId >;

			ProgramId				id;
			BindingVector			bindings;
			EntitySet				updateEntities;
			EntityProgramUpdateFunc	updateFunc;
		};

		struct EntityData
		{
			using ComponentVector = std::vector< EntityComponent* >;

			EntityId				id;
			ComponentVector			components;
		};

		using ComponentTypeMap = std::map< ComponentTypeId, ComponentData >;
		using ProgramMap = std::map< ProgramId, ProgramData >;
		using ProgramVector = std::vector< ProgramId >;
		using EntityMap = std::map< EntityId, EntityData >;

		ga_input_t*					m_pInput;
		ga_graphics_t*				m_pGraphics;

		ComponentTypeMap			m_components;

		ProgramMap					m_programs;
		ProgramVector				m_programOrder;

		EntityMap					m_entities;
		uint32_t					m_nextEntityId;

		void						buildProgramDependencies();
	};
}

