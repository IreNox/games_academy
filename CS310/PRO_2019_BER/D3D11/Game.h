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

		UINT					m_width				= 0u;
		UINT					m_height			= 0u;

		// DirectX Device
		IDXGISwapChain*			m_pSwapChain		= nullptr;
		ID3D11Device*			m_pDevice			= nullptr;
		ID3D11DeviceContext*	m_pContext			= nullptr;

		ID3D11RenderTargetView*	m_pBackBufferView	= nullptr;

		// DirectX Resources
		ID3D11VertexShader*		m_pVertexShader		= nullptr;
		ID3D11PixelShader*		m_pPixelShader		= nullptr;

		ID3D11InputLayout*		m_pVertexLayout		= nullptr;
		ID3D11Buffer*			m_pVertexBuffer		= nullptr;

		bool					initialize();
		void					shutdown();

		bool					createResources();
		void					destroyResources();

		ID3DBlob*				compileShader( const char* pShaderText, const char* pTarget );

		void					update();
		void					render();

		static LRESULT CALLBACK	windowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam );
		bool					handleMessage( unsigned int messageCode, size_t wParam );
	};
}
