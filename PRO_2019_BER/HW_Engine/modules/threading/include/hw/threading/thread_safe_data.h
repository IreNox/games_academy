#pragma once

#include "hw/threading/read_write_lock.h"

namespace hw
{
	template< class T >
	class ThreadSafeData
	{
	public:

						ThreadSafeData();
						~ThreadSafeData();

		const T&		lockRead();
		void			unlockRead();

		T&				lockWrite();
		void			unlockWrite();

	private:

		ReadWriteLock	m_lock;

		T				m_data;
	};

	template< class T >
	class ThreadSafeReadScope
	{
	public:

		ThreadSafeReadScope( ThreadSafeData< T >& data )
			: m_data( data )
			, m_value( data.lockRead() )
		{
		}

		~ThreadSafeReadScope()
		{
			m_data.unlockRead();
		}

		T* operator->()
		{
			return &m_value;
		}

	private:

		ThreadSafeData< T >&	m_data;
		T&						m_value;
	};

	template< class T >
	class ThreadSafeWriteScope
	{
	public:

		ThreadSafeWriteScope( ThreadSafeData< T >& data )
			: m_data( data )
			, m_value( data.lockWrite() )
		{
		}

		~ThreadSafeWriteScope()
		{
			m_data.unlockWrite();
		}

		T* operator->()
		{
			return &m_value;
		}

	private:

		ThreadSafeData< T >&	m_data;
		T&						m_value;
	};
}

#include "../../../src/thread_safe_data.inl"
