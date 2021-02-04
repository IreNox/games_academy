#pragma once

#include <windows.h>

namespace GA
{
	class Game
	{
	public:

		void					run();

	private:

		HWND					m_windowHandle	= nullptr;
		bool					m_isOpen		= false;

		bool					initialize();
		void					shutdown();

		void					update();
		void					render();

		static LRESULT CALLBACK	windowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
		bool					handleMessage( unsigned int messageCode, size_t wParam );
	};
}
