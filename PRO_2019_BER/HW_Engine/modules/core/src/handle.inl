#pragma once

namespace hw
{
	template< class TTag, class TStorage, uint32 TIndexBits >
	void Handle<TTag, TStorage, TIndexBits>::set( TStorage index, TStorage counter )
	{
		assert( (((1u << TIndexBits) - 1u) & index) == index );
		m_value = ((counter + 1u) << TIndexBits) | index;
	}

	template< class TTag, class TStorage, uint32 TIndexBits >
	Handle<TTag, TStorage, TIndexBits> Handle<TTag, TStorage, TIndexBits>::invalid()
	{
		return Handle( 0u );
	}
}