#pragma once

#include <Windows.h>

namespace hw
{
	class ReadWriteLock
	{
	public:

		bool	create();
		void	destroy();

		void	lockRead();
		void	unlockRead();

		void	lockWrite();
		void	unlockWrite();

	private:

		SRWLOCK	m_lock;
	};
}