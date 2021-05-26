#pragma once

#include "hw/core/types.h"
#include "hw/threading/atomic.h"

#include <Windows.h>

namespace hw
{
	class Thread;
	typedef uint32(*ThreadFunc)( const Thread& );

	class Thread
	{
	public:

						Thread();
						~Thread();

		bool			create( ThreadFunc threadFunc, void* pArgument );
		void			destroy();

		void			requestQuit();
		bool			isQuitRequested() const;

		void*			getArgument() const { return m_pArgument; }

	private:

		uint32_atomic	m_isQuitRequested;
		void*			m_pArgument;
		ThreadFunc		m_pStartFunc;

		HANDLE			m_handle;

		static DWORD	threadStart( LPVOID lpThreadParameter );
	};
}