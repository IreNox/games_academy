#pragma once

#include "hw/core/types.h"

namespace hw
{
	class MemoryAllocator
	{
	public:

		virtual void*	allocate( size_t size, size_t alignment = DefaultAlignment ) = 0;
		virtual void*	reallocate( void* pMemory, size_t size, size_t alignment = DefaultAlignment ) = 0;
		virtual void	free( void* pMemory ) = 0;
	};

	int					compareMemory( const void* pMemory1, const void* pMemory2, size_t size );
	void				copyMemory( void* pTarget, const void* pSource, size_t size );
	void				setMemory( void* pTarget, uint8 data, size_t size);
	void				zeroMemory( void* pTarget, size_t size );
}