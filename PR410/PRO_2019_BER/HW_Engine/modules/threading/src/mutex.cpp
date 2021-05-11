#include "hw/threading/mutex.h"

namespace hw
{
	bool Mutex::create()
	{
		InitializeCriticalSection( &m_mutex );
		return true;
	}

	void Mutex::destroy()
	{
		DeleteCriticalSection( &m_mutex );
	}

	void Mutex::lock()
	{
		EnterCriticalSection( &m_mutex );
	}

	bool Mutex::tryLock()
	{
		return TryEnterCriticalSection( &m_mutex ) == TRUE;
	}

	void Mutex::unlock()
	{
		LeaveCriticalSection( &m_mutex );
	}
}