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
}