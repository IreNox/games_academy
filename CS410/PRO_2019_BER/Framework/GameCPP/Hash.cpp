#include "Hash.h"

namespace GA
{
	static const uint32_t Fnv1aInital = 2166136261u;
	static const uint32_t Fnv1aMul = 16777619u;

	uint32_t fnv1aHash( const void* pData, size_t size )
	{
		const uint8_t* pBytes = (const uint8_t*)pData;

		uint32_t hash = Fnv1aInital;
		for( size_t i = 0u; i < size; ++i )
		{
			hash = (hash ^ uint32_t( pBytes[ i ] )) * Fnv1aMul;
		}

		return hash;
	}

	uint32_t getValueHash( uint32_t value )
	{
		return fnv1aHash( &value, sizeof( value ) );
	}

	uint32_t getValueHash( uint64_t value )
	{
		return fnv1aHash( &value, sizeof( value ) );
	}
}
