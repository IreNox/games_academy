#pragma once

#include "hw/core/types.h"

namespace hw
{
	template< class TTag, class TStorage, uint32 TIndexBits >
	class Handle
	{
	public:

						Handle();
		explicit		Handle( TStorage value );
						Handle( TStorage index, TStorage counter );

		bool			isValid() const;
		bool			isInvalid() const;

		TStorage		getIndex() const;
		TStorage		getCounter() const;

		void			set( TStorage index, TStorage counter );

		static Handle	invalid();

		bool			operator==( const Handle& rhs ) const;
		bool			operator!=( const Handle& rhs ) const;

	public:

		TStorage		m_value;
	};
}

#include "../../../src/handle.inl"
