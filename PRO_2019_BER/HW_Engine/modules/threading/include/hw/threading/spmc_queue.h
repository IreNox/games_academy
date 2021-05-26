#pragma once

#include "hw/threading/atomic.h"

namespace hw
{
	template< class T >
	class SPMCQueue
	{
	public:

						SPMCQueue();
						~SPMCQueue();

		bool			create( size_t capacity );
		void			destroy();

		bool			isEmpty() const;

		bool			push( const T& value );
		bool			pop( T& target );

	private:

		T*				m_pData;
		size_t			m_capacity;
		size_t			m_capacityMask;

		uint64_atomic	m_top;
		uint64_atomic	m_bottom;
	};
}

#include "../../../src/spmc_queue.inl"
