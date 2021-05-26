#include "hw/threading/semaphore.h"

namespace hw
{
	Semaphore::Semaphore()
	{
		m_semaphore = NULL;
	}

	Semaphore::~Semaphore()
	{
		destroy();
	}

	bool Semaphore::create()
	{
		m_semaphore = CreateSemaphore( nullptr, 0u, 0xffffffff, L"Semaphore" );
		return m_semaphore != NULL;
	}

	void Semaphore::destroy()
	{
		if( m_semaphore == NULL )
		{
			return;
		}

		CloseHandle( m_semaphore );
		m_semaphore = NULL;
	}

	void Semaphore::increment()
	{
		ReleaseSemaphore( m_semaphore, 1u, nullptr );
	}

	void Semaphore::decrement()
	{
		WaitForSingleObject( m_semaphore, INFINITE );
	}
}
