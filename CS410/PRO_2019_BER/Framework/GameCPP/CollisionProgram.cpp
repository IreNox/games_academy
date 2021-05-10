#include "CollisionProgram.h"

#include "Transform.h"
#include "Collision.h"

#include "framework.h"

namespace GA
{
	static const EntityProgramComponentBinding s_collisionBindings[] =
	{
		{ TransformComponent::TypeId, EntityProgramIoType::Read },
		{ CollisionComponent::TypeId, EntityProgramIoType::ReadWrite }
	};

	void CollisionProgram::registerProgram( EntitySystem& system )
	{
		system.registerProgram( ProgramId, s_collisionBindings, ARRAY_COUNT( s_collisionBindings ), update );
	}

	void CollisionProgram::update( const EntityUpdateContext& context, const EntityProgrammTupleIterator* pData, size_t dataCount )
	{

	}

}
