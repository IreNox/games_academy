#pragma once

namespace hw
{
	template< class T >
	ThreadSafeData<T>::ThreadSafeData()
	{
		m_lock.create();
	}

	template< class T >
	ThreadSafeData<T>::~ThreadSafeData()
	{
		m_lock.destroy();
	}

	template< class T >
	const T& ThreadSafeData<T>::lockRead()
	{
		m_lock.lockRead();
		return m_data;
	}

	template< class T >
	void ThreadSafeData<T>::unlockRead()
	{
		m_lock.unlockRead();
	}

	template< class T >
	T& ThreadSafeData<T>::lockWrite()
	{
		m_lock.lockWrite();
		return m_data;
	}

	template< class T >
	void ThreadSafeData<T>::unlockWrite()
	{
		m_lock.unlockWrite();
	}
}