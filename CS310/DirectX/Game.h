#pragma once

#include <windows.h>
#include <d3d11.h>

namespace GA
{
	class Game
	{
	public:

		void					run();

	private:

		// Window
		HWND					m_windowHandle		= nullptr;
		bool					m_isOpen			= false;

		// DirectX Device
		IDXGISwapChain*			m_pSwapChain		= nullptr;
		ID3D11Device*			m_pDevice			= nullptr;
		ID3D11DeviceContext*	m_pContext			= nullptr;

		ID3D11RenderTargetView*	m_pBackBufferView	= nullptr;

		bool					initialize();
		void					shutdown();

		void					update();
		void					render();

		static LRESULT CALLBACK	windowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
		bool					handleMessage( unsigned int messageCode, size_t wParam );
	};
}
