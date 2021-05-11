#include "hw/threading/thread.h"

namespace hw
{
	Thread::Thread()
	{
		AtomicUInt32StoreReleaxed( &m_isQuitRequested, 0u );
		m_pArgument	= nullptr;
		m_handle	= NULL;
	}

	Thread::~Thread()
	{
		destroy();
	}

	bool Thread::create( ThreadFunc threadFunc, void* pArgument )
	{
		AtomicUInt32StoreReleaxed( &m_isQuitRequested, 0u );
		m_pArgument		= pArgument;
		m_pStartFunc	= threadFunc;

		m_handle = CreateThread( nullptr, 0u, threadStart, this, 0u, nullptr );
		if( m_handle == NULL )
		{
			return false;
		}

		return true;
	}

	void Thread::destroy()
	{
		if( m_handle == NULL )
		{
			return;
		}

		requestQuit();
		WaitForSingleObject( m_handle, INFINITE );
		CloseHandle( m_handle );

		m_handle = NULL;
	}

	void Thread::requestQuit()
	{
		AtomicUInt32StoreReleaxed( &m_isQuitRequested, 1u );
	}

	bool Thread::isQuitRequested() const
	{
		return AtomicUInt32LoadReleaxed( &m_isQuitRequested ) != 0u;
	}

	DWORD Thread::threadStart( LPVOID lpThreadParameter )
	{
		const Thread& thread = *(const Thread*)lpThreadParameter;
		return (DWORD)thread.m_pStartFunc( thread );
	}
}