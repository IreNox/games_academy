#include "Game.h"

namespace GA
{
	static constexpr int	WindowWidth		= 1280;
	static constexpr int	WindowHeight	= 720;

	static const wchar_t*	s_pWindowTitle	= L"CS310 - DirectX";

	void Game::run()
	{
		if( !initialize() )
		{
			return;
		}

		while( m_isOpen )
		{
			update();
			render();
		}

		shutdown();
	}

	bool Game::initialize()
	{
		const HINSTANCE	hInstance = GetModuleHandle( nullptr );

		WNDCLASSEXW windowClass = {};
		windowClass.cbSize			= sizeof( WNDCLASSEXW );
		windowClass.hInstance		= hInstance;
		windowClass.lpfnWndProc		= &Game::windowProc;
		windowClass.lpszClassName	= L"GAWindowClass";
		windowClass.hbrBackground	= (HBRUSH)COLOR_WINDOW;
		windowClass.hCursor			= LoadCursor( nullptr, IDC_ARROW );

		HRESULT result = RegisterClassExW( &windowClass );
		if( FAILED( result ) )
		{
			return false;
		}

		m_windowHandle = CreateWindow(
			L"GAWindowClass",
			s_pWindowTitle,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			WindowWidth,
			WindowHeight,
			nullptr,
			nullptr,
			hInstance,
			nullptr
		);

		if( m_windowHandle == nullptr )
		{
			return false;
		}

		SetWindowLongPtr( m_windowHandle, GWLP_USERDATA, (LONG_PTR)this );

		ShowWindow( m_windowHandle, SW_SHOWNORMAL );
		UpdateWindow( m_windowHandle );

		RECT clientRect;
		GetClientRect( m_windowHandle, &clientRect );

		m_isOpen = true;

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount		= 2u;
		swapChainDesc.BufferDesc.Format	= DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.Width	= (clientRect.right - clientRect.left);
		swapChainDesc.BufferDesc.Height	= (clientRect.bottom - clientRect.top);
		swapChainDesc.BufferUsage		= DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow		= m_windowHandle;
		swapChainDesc.SampleDesc.Count	= 1;
		swapChainDesc.Windowed			= TRUE;
		swapChainDesc.SwapEffect		= DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.Flags				= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

		const D3D_FEATURE_LEVEL supportedFeatureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0
		};

		UINT deviceFlags = D3D11_CREATE_DEVICE_SINGLETHREADED;
#ifdef _DEBUG
		deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		D3D_FEATURE_LEVEL selectedFeatureLevel;
		result = D3D11CreateDeviceAndSwapChain(
			nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			nullptr,
			deviceFlags,
			supportedFeatureLevels,
			1u,
			D3D11_SDK_VERSION,
			&swapChainDesc,
			&m_pSwapChain,
			&m_pDevice,
			&selectedFeatureLevel,
			&m_pContext
		);

		if( FAILED( result ) )
		{
			shutdown();
			return false;
		}

		ID3D11Texture2D* pBackBuffer = nullptr;
		if( FAILED( m_pSwapChain->GetBuffer( 0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer ) ) )
		{
			shutdown();
			return false;
		}

		if( FAILED( m_pDevice->CreateRenderTargetView( pBackBuffer, nullptr, &m_pBackBufferView ) ) )
		{
			pBackBuffer->Release();
			shutdown();
			return false;
		}

		pBackBuffer->Release();

		return true;
	}

	void Game::shutdown()
	{
		if( m_pBackBufferView != nullptr )
		{
			m_pBackBufferView->Release();
			m_pBackBufferView = nullptr;
		}

		if( m_pContext != nullptr )
		{
			m_pContext->Release();
			m_pContext = nullptr;
		}

		if( m_pDevice != nullptr )
		{
			m_pDevice->Release();
			m_pDevice = nullptr;
		}

		if( m_pSwapChain != nullptr )
		{
			m_pSwapChain->Release();
			m_pSwapChain = nullptr;
		}

		if( m_windowHandle != nullptr )
		{
			DestroyWindow( m_windowHandle );
			m_windowHandle = nullptr;
		}
	}

	void Game::update()
	{
		MSG msg;
		while( PeekMessage( &msg, nullptr, 0U, 0U, PM_REMOVE ) )
		{
			TranslateMessage( &msg );
			DispatchMessage( &msg );
		}
	}

	void Game::render()
	{
		const float backgroundColor[] = { 0.0f, 0.5f, 1.0f, 1.0f };
		m_pContext->ClearRenderTargetView( m_pBackBufferView, backgroundColor );

		m_pSwapChain->Present( 1, 0 );
	}

	LRESULT CALLBACK Game::windowProc( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam )
	{
		Game* pGame = (Game*)GetWindowLongPtr( hWnd, GWLP_USERDATA );
		if( pGame != nullptr &&
			pGame->handleMessage( message, wParam ) )
		{
			return 0u;
		}

		switch( message )
		{
		case WM_DESTROY:
			PostQuitMessage( 0 );
			break;

		default:
			return DefWindowProc( hWnd, message, wParam, lParam );
			break;
		}

		return 0;
	}

	bool Game::handleMessage( unsigned int messageCode, size_t wParam )
	{
		switch( messageCode )
		{
		case WM_CLOSE:
			m_isOpen = false;
			return true;

		default:
			break;
		}

		return false;
	}
}
