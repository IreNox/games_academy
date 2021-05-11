#include "hw/threading/atomic.h"

#include <Windows.h>

namespace hw
{
	uint32 AtomicUInt32LoadReleaxed( const uint32_atomic* pTarget )
	{
		return InterlockedOrNoFence( (LONG volatile*)&pTarget->value, 0u );
	}

	void AtomicUInt32StoreReleaxed( uint32_atomic* pTarget, uint32 value )
	{
		InterlockedExchangeNoFence( (LONG volatile*)&pTarget->value, value );
	}

	//////////////////////////////////////////////////////////////////////////
	// 64 bit

	uint64 AtomicUInt64LoadReleaxed( const uint64_atomic* pTarget )
	{
		return InterlockedOr64NoFence( (LONG64 volatile*)&pTarget->value, 0u );
	}

	uint64 AtomicUInt64LoadAcquire( const uint64_atomic* pTarget )
	{
		return InterlockedOr64Acquire( (LONG64 volatile*)&pTarget->value, 0u );
	}

	uint64 AtomicUInt64LoadRelease( const uint64_atomic* pTarget )
	{
		return InterlockedOr64Release( (LONG64 volatile*)&pTarget->value, 0u );
	}

	void AtomicUInt64StoreReleaxed( uint64_atomic* pTarget, uint64 value )
	{
		InterlockedExchangeNoFence64( (LONG64 volatile*)&pTarget->value, value );
	}

	void AtomicUInt64StoreAcquire( uint64_atomic* pTarget, uint64 value )
	{
		InterlockedExchangeAcquire64( (LONG64 volatile*)&pTarget->value, value );
	}

	void AtomicUInt64StoreRelease( uint64_atomic* pTarget, uint64 value )
	{
		InterlockedExchange64( (LONG64 volatile*)&pTarget->value, value );
	}

	uint64 AtomicUInt64IncReleaxed( uint64_atomic* pTarget )
	{
		return InterlockedIncrementNoFence64( (LONG64 volatile*)&pTarget->value );
	}

	uint64 AtomicUInt64IncAcquire( uint64_atomic* pTarget )
	{
		return InterlockedIncrementAcquire64( (LONG64 volatile*)&pTarget->value );
	}

	uint64 AtomicUInt64IncRelease( uint64_atomic* pTarget )
	{
		return InterlockedIncrementRelease64( (LONG64 volatile*)&pTarget->value );
	}

	uint64 AtomicUInt64DecReleaxed( uint64_atomic* pTarget )
	{
		return InterlockedDecrementNoFence64( (LONG64 volatile*)&pTarget->value );
	}

	uint64 AtomicUInt64DecAcquire( uint64_atomic* pTarget )
	{
		return InterlockedDecrementAcquire64( (LONG64 volatile*)&pTarget->value );
	}

	uint64 AtomicUInt64DecRelease( uint64_atomic* pTarget )
	{
		return InterlockedDecrementRelease64( (LONG64 volatile*)&pTarget->value );
	}

	uint64 AtomicUInt64CompareStoreReleaxed( uint64_atomic* pTarget, uint64 compare, uint64 newValue )
	{
		return InterlockedCompareExchangeNoFence64( (LONG64 volatile*)&pTarget->value, newValue, compare );
	}

	uint64 AtomicUInt64CompareStoreAcquire( uint64_atomic* pTarget, uint64 compare, uint64 newValue )
	{
		return InterlockedCompareExchangeAcquire64( (LONG64 volatile*)&pTarget->value, newValue, compare );
	}

	uint64 AtomicUInt64CompareStoreRelease( uint64_atomic* pTarget, uint64 compare, uint64 newValue )
	{
		return InterlockedCompareExchangeRelease64( (LONG64 volatile*)&pTarget->value, newValue, compare );
	}
}