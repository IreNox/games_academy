#pragma once

#include "EntitySystem.h"

namespace GA
{
	class BallProgram
	{
	public:

		static constexpr ProgramId	ProgramId = 0x26a928aeu;
		static void					registerProgram( EntitySystem& system );

	private:

		static void					update( const EntityUpdateContext& context, const EntityProgrammTupleIterator* pData, size_t dataCount );
	};
}
