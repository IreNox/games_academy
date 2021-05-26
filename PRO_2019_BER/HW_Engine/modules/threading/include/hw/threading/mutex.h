#pragma once

#include <Windows.h>

namespace hw
{
	class Mutex
	{
	public:

		bool				create();
		void				destroy();

		void				lock();
		bool				tryLock();
		void				unlock();

	private:

		CRITICAL_SECTION	m_mutex;
	};

	class MutexLock
	{
	public:

		MutexLock( Mutex& mutex )
			: m_mutex( mutex )
		{
			mutex.lock();
		}

		~MutexLock()
		{
			m_mutex.unlock();
		}

	private:

		Mutex&		m_mutex;
	};
}