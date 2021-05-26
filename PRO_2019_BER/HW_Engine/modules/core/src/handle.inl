#pragma once

#include <assert.h>

namespace hw
{
	template< class TTag, class TStorage, uint32 TIndexBits >
	Handle<TTag, TStorage, TIndexBits>::Handle()
	{
	}

	template< class TTag, class TStorage, uint32 TIndexBits >
	Handle<TTag, TStorage, TIndexBits>::Handle( TStorage value )
	{
		m_value = value;
	}

	template< class TTag, class TStorage, uint32 TIndexBits >
	bool Handle<TTag, TStorage, TIndexBits>::isValid() const
	{
		return m_value != 0u;
	}

	template< class TTag, class TStorage, uint32 TIndexBits >
	bool Handle<TTag, TStorage, TIndexBits>::isInvalid() const
	{
		return m_value == 0u;
	}

	template< class TTag, class TStorage, uint32 TIndexBits >
	TStorage Handle<TTag, TStorage, TIndexBits>::getIndex() const
	{
		return m_value & ((TStorage(1u) << TIndexBits) - 1u);
	}

	template< class TTag, class TStorage, uint32 TIndexBits >
	TStorage Handle<TTag, TStorage, TIndexBits>::getCounter() const
	{
		return m_value >> TIndexBits;
	}

	template< class TTag, class TStorage, uint32 TIndexBits >
	void Handle<TTag, TStorage, TIndexBits>::set( TStorage index, TStorage counter )
	{
		assert( (((TStorage(1u) << TIndexBits) - 1u) & index) == index );
		m_value = ((counter + 1u) << TIndexBits) | index;
	}

	template< class TTag, class TStorage, uint32 TIndexBits >
	Handle<TTag, TStorage, TIndexBits> Handle<TTag, TStorage, TIndexBits>::invalid()
	{
		return Handle( 0u );
	}

	template< class TTag, class TStorage, uint32 TIndexBits >
	bool Handle<TTag, TStorage, TIndexBits>::operator==( const Handle& rhs ) const
	{
		return m_value == rhs.m_value;
	}

	template< class TTag, class TStorage, uint32 TIndexBits >
	bool Handle<TTag, TStorage, TIndexBits>::operator!=( const Handle& rhs ) const
	{
		return m_value != rhs.m_value;
	}
}