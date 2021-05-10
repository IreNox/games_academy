#pragma once

#include "EntitySystem.h"

namespace GA
{
	class PlayerProgram
	{
	public:

		static constexpr ProgramId	ProgramId = 0x881d74b0u;
		static void					registerProgram( EntitySystem& system );

	private:

		static void					update( const EntityUpdateContext& context, const EntityProgrammTupleIterator* pData, size_t dataCount );
	};
}


