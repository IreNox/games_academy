#pragma once

#include <assert.h>

namespace hw
{
	template< class T >
	SPMCQueue<T>::SPMCQueue()
	{
		m_pData		= nullptr;
		m_capacity	= 0u;
	}

	template< class T >
	SPMCQueue<T>::~SPMCQueue()
	{
		destroy();
	}

	template< class T >
	bool SPMCQueue<T>::create( size_t capacity )
	{
		assert( capacity > 1u && __popcnt64( capacity ) == 1u ); // must be power of two

		m_pData			= new T[ capacity ];
		m_capacity		= capacity;
		m_capacityMask	= capacity - 1u;

		AtomicUInt64StoreReleaxed( &m_top, 0u );
		AtomicUInt64StoreReleaxed( &m_bottom, 0u );

		return true;
	}

	template< class T >
	void SPMCQueue<T>::destroy()
	{
		if( m_pData == nullptr )
		{
			return;
		}

		delete[] m_pData;
		m_pData = nullptr;

		m_capacity = 0u;
	}

	template< class T >
	bool SPMCQueue<T>::isEmpty() const
	{
		return AtomicUInt64LoadReleaxed( &m_top ) == AtomicUInt64LoadReleaxed( &m_bottom );
	}

	template< class T >
	bool SPMCQueue<T>::push( const T& value )
	{
		const uint64 bottom = AtomicUInt64LoadAcquire( &m_bottom ) & m_capacityMask;
		if( bottom + 1u == AtomicUInt64LoadReleaxed( &m_top ) )
		{
			// full
			return false;
		}

		const uint64 bottomIndex = bottom & m_capacityMask;
		assert( bottomIndex < m_capacity );
		m_pData[ bottomIndex ] = value;
		AtomicUInt64IncRelease( &m_bottom );

		return true;
	}

	template< class T >
	bool SPMCQueue<T>::pop( T& target )
	{
		while( true )
		{
			const uint64 top = AtomicUInt64LoadAcquire( &m_top );
			if( top == AtomicUInt64LoadReleaxed( &m_bottom ) )
			{
				// empty
				return false;
			}

			const uint64 topIndex = top & m_capacityMask;
			target = m_pData[ topIndex ];

			if( AtomicUInt64CompareStoreRelease( &m_top, top, top + 1u ) == top )
			{
				return true;
			}
		}

		return false;
	}
}
