#pragma once

#include "EntitySystem.h"

namespace GA
{
	class CollisionProgram
	{
	public:

		static constexpr ProgramId	ProgramId = 0xb694d2c9u;
		static void					registerProgram( EntitySystem& system );

	private:

		static void					update( const EntityUpdateContext& context, const EntityProgrammTupleIterator* pData, size_t dataCount );
	};
}


