#pragma once

#include <Windows.h>

namespace hw
{
	class Event
	{
	public:

				Event();
				~Event();

		bool	create();
		void	destroy();

		void	signal();
		void	wait();

	private:

		HANDLE	m_event;
	};
}