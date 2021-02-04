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

		return true;
	}

	void Game::shutdown()
	{
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
