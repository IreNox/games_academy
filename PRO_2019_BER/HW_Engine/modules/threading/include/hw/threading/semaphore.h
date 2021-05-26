#pragma once

#include <Windows.h>

namespace hw
{
	class Semaphore
	{
	public:

				Semaphore();
				~Semaphore();

		bool	create();
		void	destroy();

		void	increment();
		void	decrement();

	private:

		HANDLE	m_semaphore;
	};
}