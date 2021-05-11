#pragma once

#include "hw/core/types.h"

namespace hw
{
	struct uint32_atomic
	{
		uint32		value;
	};

	struct uint64_atomic
	{
		uint64		value;
	};

	// Returns the new value
	uint32		AtomicLoadReleaxed( const uint32_atomic* pTarget );
	uint32		AtomicLoadAquire( const uint32_atomic* pTarget );
	uint32		AtomicLoadRelease( const uint32_atomic* pTarget );

	void		AtomicStoreReleaxed( uint32_atomic* pTarget, uint32 value );
	void		AtomicStoreAquire( uint32_atomic* pTarget, uint32 value );
	void		AtomicStoreRelease( uint32_atomic* pTarget, uint32 value );

	uint32		AtomicIncrementReleaxed( uint32_atomic* pTarget );
	uint32		AtomicIncrementAquire( uint32_atomic* pTarget );
	uint32		AtomicIncrementRelease( uint32_atomic* pTarget );

	uint32		AtomicDecrement( uint32_atomic* pTarget );
	uint32		AtomicAdd( uint32_atomic* pTarget, uint32 value );
	uint32		AtomicSub( uint32_atomic* pTarget, uint32 value );
	uint32		AtomicAnd( uint32_atomic* pTarget, uint32 value );
	uint32		AtomicOr( uint32_atomic* pTarget, uint32 value );
	uint32		AtomicXor( uint32_atomic* pTarget, uint32 value );

	uint64		AtomicIncrement( uint64_atomic* pTarget );
	uint64		AtomicDecrement( uint64_atomic* pTarget );
	uint64		AtomicAdd( uint64_atomic* pTarget, uint64 value );
	uint64		AtomicSub( uint64_atomic* pTarget, uint64 value );
	uint64		AtomicAnd( uint64_atomic* pTarget, uint64 value );
	uint64		AtomicOr( uint64_atomic* pTarget, uint64 value );
	uint64		AtomicXor( uint64_atomic* pTarget, uint64 value );
}
