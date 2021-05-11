#include "hw/threading/event.h"

namespace hw
{
	Event::Event()
	{
		m_event = NULL;
	}

	Event::~Event()
	{
		destroy();
	}

	bool Event::create()
	{
		m_event = CreateEvent( nullptr, FALSE, FALSE, L"Event" );
		return m_event != NULL;
	}

	void Event::destroy()
	{
		if( m_event == NULL )
		{
			return;
		}

		CloseHandle( m_event );
		m_event = NULL;
	}

	void Event::signal()
	{
		SetEvent( m_event );
	}

	void Event::wait()
	{
		WaitForSingleObject( m_event, INFINITE );
	}
}
