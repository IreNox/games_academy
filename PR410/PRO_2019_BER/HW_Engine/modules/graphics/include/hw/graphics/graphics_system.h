#pragma once

#include "hw/core/types.h"

#include <windows.h>
#include <d3d11.h>

#define ARRAY_COUNT( var ) (sizeof((var))/sizeof(*(var)))

namespace hw
{
	struct GameVertex
	{
		float	position[ 3u ];
		float	color[ 4u ];
	};

	class GraphicsSystem
	{
	public:

		bool					create();
		void					destroy();

		void					update();

		ID3D11DeviceContext*	beginFrame( const float backgroundColor[ 4u ] );
		void					endFrame();

		void					draw( const GameVertex* pVertives, UINT vertexCount );
		void					drawRect( float x, float y, float w, float h, uint32 color );

		HWND					getHandle() { return m_windowHandle; }
		bool					isOpen() { return m_isOpen; }

		ID3D11Device*			getDevice() { return m_pDevice; }

		ID3D11RenderTargetView*	getBackBuffer() { return m_pBackBufferView; }
		UINT					getBackBufferWidth() { return m_width; }
		UINT					getBackBufferHeight() { return m_height; }

	private:

		// Window
		HWND					m_windowHandle = nullptr;
		bool					m_isOpen = false;

		UINT					m_width = 0u;
		UINT					m_height = 0u;

		// DirectX Device
		IDXGISwapChain*			m_pSwapChain = nullptr;
		ID3D11Device*			m_pDevice = nullptr;
		ID3D11DeviceContext*	m_pContext = nullptr;

		ID3D11RenderTargetView*	m_pBackBufferView = nullptr;

		// DirectX Resources
		ID3D11VertexShader*		m_pVertexShader = nullptr;
		ID3D11PixelShader*		m_pPixelShader = nullptr;

		ID3D11InputLayout*		m_pVertexLayout = nullptr;
		ID3D11Buffer*			m_pVertexBuffer = nullptr;

		ID3D11Buffer*			m_pConstantBuffer = nullptr;

		bool					createResources();
		void					destroyResources();

		ID3DBlob*				compileShader(const char* pShaderText, const char* pTarget);

		static LRESULT CALLBACK	windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
		bool					handleMessage(unsigned int messageCode, size_t wParam);
	};
}

