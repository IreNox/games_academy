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
	uint32		AtomicUInt32LoadReleaxed( const uint32_atomic* pTarget );
	uint32		AtomicUInt32LoadAcquire( const uint32_atomic* pTarget );
	uint32		AtomicUInt32LoadRelease( const uint32_atomic* pTarget );

	void		AtomicUInt32StoreReleaxed( uint32_atomic* pTarget, uint32 value );
	void		AtomicUInt32StoreAcquire( uint32_atomic* pTarget, uint32 value );
	void		AtomicUInt32StoreRelease( uint32_atomic* pTarget, uint32 value );

	uint32		AtomicIncrementReleaxed( uint32_atomic* pTarget );
	uint32		AtomicIncrementAquire( uint32_atomic* pTarget );
	uint32		AtomicIncrementRelease( uint32_atomic* pTarget );

	uint32		AtomicDecrement( uint32_atomic* pTarget );
	uint32		AtomicAdd( uint32_atomic* pTarget, uint32 value );
	uint32		AtomicSub( uint32_atomic* pTarget, uint32 value );
	uint32		AtomicAnd( uint32_atomic* pTarget, uint32 value );
	uint32		AtomicOr( uint32_atomic* pTarget, uint32 value );
	uint32		AtomicXor( uint32_atomic* pTarget, uint32 value );

	// 64 bit
	uint64		AtomicUInt64LoadReleaxed( const uint64_atomic* pTarget );
	uint64		AtomicUInt64LoadAcquire( const uint64_atomic* pTarget );
	uint64		AtomicUInt64LoadRelease( const uint64_atomic* pTarget );

	void		AtomicUInt64StoreReleaxed( uint64_atomic* pTarget, uint64 value );
	void		AtomicUInt64StoreAcquire( uint64_atomic* pTarget, uint64 value );
	void		AtomicUInt64StoreRelease( uint64_atomic* pTarget, uint64 value );

	uint64		AtomicUInt64IncReleaxed( uint64_atomic* pTarget );
	uint64		AtomicUInt64IncAcquire( uint64_atomic* pTarget );
	uint64		AtomicUInt64IncRelease( uint64_atomic* pTarget );

	uint64		AtomicUInt64DecReleaxed( uint64_atomic* pTarget );
	uint64		AtomicUInt64DecAcquire( uint64_atomic* pTarget );
	uint64		AtomicUInt64DecRelease( uint64_atomic* pTarget );

	uint64		AtomicUInt64CompareStoreReleaxed( uint64_atomic* pTarget, uint64 compare, uint64 newValue );
	uint64		AtomicUInt64CompareStoreAcquire( uint64_atomic* pTarget, uint64 compare, uint64 newValue );
	uint64		AtomicUInt64CompareStoreRelease( uint64_atomic* pTarget, uint64 compare, uint64 newValue );
}
