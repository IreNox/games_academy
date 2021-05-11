#include "hw/threading/atomic.h"

#include <Windows.h>

namespace hw
{
	uint32 AtomicLoadReleaxed( const uint32_atomic* pTarget )
	{
		return InterlockedOrNoFence( (LONG volatile*)&pTarget->value, 0u );
	}

	void AtomicStoreReleaxed( uint32_atomic* pTarget, uint32 value )
	{
		InterlockedExchangeNoFence( (LONG volatile*)&pTarget->value, value );
	}
}