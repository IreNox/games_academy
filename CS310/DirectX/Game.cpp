#include "Game.h"

#include <d3dcompiler.h>

namespace GA
{
	static constexpr int	WindowWidth		= 1280;
	static constexpr int	WindowHeight	= 720;

	static const wchar_t*	s_pWindowTitle	= L"CS310 - DirectX";

	struct GameVertex
	{
		float	position[ 3u ];
		float	color[ 4u ];
	};

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

		if( !createResources() )
		{
			shutdown();
			return false;
		}

		return true;
	}

	void Game::shutdown()
	{
		destroyResources();

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

	bool Game::createResources()
	{
		const char* pVertexShader = R"V0G0N(
			struct VertexInput
			{
				float3	position	: POSITION0;
				float4	color		: COLOR0;
			};

			struct VertexToPixel
			{
				float4	position	: SV_POSITION0;
				float4	color		: COLOR0;
			};

			VertexToPixel main( VertexInput input )
			{
				VertexToPixel output;
				output.position	= float4( input.position, 1.0 );
				output.color	= input.color;

				return output;
			}
		)V0G0N";

		ID3DBlob* pVertexShaderBlob = compileShader( pVertexShader, "vs_5_0" );
		if( pVertexShaderBlob == nullptr )
		{
			return false;
		}

		HRESULT result = m_pDevice->CreateVertexShader( pVertexShaderBlob->GetBufferPointer(), pVertexShaderBlob->GetBufferSize(), nullptr, &m_pVertexShader );
		if( FAILED( result ) )
		{
			pVertexShaderBlob->Release();
			return false;
		}

		const D3D11_INPUT_ELEMENT_DESC inputElements[] =
		{
			{ "POSITION",	0u,	DXGI_FORMAT_R32G32B32_FLOAT,	0u,	D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0u },
			{ "COLOR",		0u, DXGI_FORMAT_R32G32B32A32_FLOAT,	0u, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0u }
		};

		result = m_pDevice->CreateInputLayout( inputElements, 2u, pVertexShaderBlob->GetBufferPointer(), pVertexShaderBlob->GetBufferSize(), &m_pVertexLayout );
		pVertexShaderBlob->Release();

		if( FAILED( result ) )
		{
			return false;
		}

		const char* pPixelShader = R"V0G0N(
			struct VertexToPixel
			{
				float4	position	: SV_POSITION0;
				float4	color		: COLOR0;
			};

			struct PixelOutput
			{
				float4	color		: SV_TARGET0;
			};

			PixelOutput main( VertexToPixel input )
			{
				PixelOutput output;
				output.color = input.color;

				return output;
			}
		)V0G0N";

		ID3DBlob* pPixelShaderBlob = compileShader( pPixelShader, "ps_5_0" );
		if( pPixelShaderBlob == nullptr )
		{
			return false;
		}

		result = m_pDevice->CreatePixelShader( pPixelShaderBlob->GetBufferPointer(), pPixelShaderBlob->GetBufferSize(), nullptr, &m_pPixelShader );
		pPixelShaderBlob->Release();
		if( FAILED( result ) )
		{
			return false;
		}

		//struct GameVertex
		//{
		//	float	position[ 3u ];
		//	float	color[ 4u ];
		//};

		const GameVertex vertices[] =
		{
			{ {  0.0f, -0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			{ {  0.5f,  0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
			{ { -0.5f,  0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
		};

		D3D11_BUFFER_DESC vertexBuferDesc = {};
		vertexBuferDesc.ByteWidth	= sizeof( vertices );
		vertexBuferDesc.Usage		= D3D11_USAGE_IMMUTABLE;
		vertexBuferDesc.BindFlags	= D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexData = {};
		vertexData.pSysMem			= vertices;

		if( FAILED( m_pDevice->CreateBuffer( &vertexBuferDesc, &vertexData, &m_pVertexBuffer ) ) )
		{
			return false;
		}

		return true;
	}

	void Game::destroyResources()
	{
		if( m_pVertexBuffer != nullptr )
		{
			m_pVertexBuffer->Release();
			m_pVertexBuffer = nullptr;
		}

		if( m_pVertexLayout != nullptr )
		{
			m_pVertexLayout->Release();
			m_pVertexLayout = nullptr;
		}

		if( m_pPixelShader != nullptr )
		{
			m_pPixelShader->Release();
			m_pPixelShader = nullptr;
		}

		if( m_pVertexShader != nullptr )
		{
			m_pVertexShader->Release();
			m_pVertexShader = nullptr;
		}
	}

	ID3DBlob* Game::compileShader( const char* pShaderText, const char* pTarget )
	{
		ID3DBlob* pShaderBlob = nullptr;
		ID3DBlob* pErrorBlob = nullptr;

		UINT flags = 0;
#ifdef _DEBUG
		flags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
		HRESULT result = D3DCompile( pShaderText, strlen( pShaderText ), "Shader", nullptr, nullptr, "main", pTarget, flags, 0, &pShaderBlob, &pErrorBlob );
		if( FAILED( result ) )
		{
			MessageBoxA( m_windowHandle, (const char*)pErrorBlob->GetBufferPointer(), "DirectX", MB_ICONSTOP );

			pErrorBlob->Release();
			return nullptr;
		}

		if( pErrorBlob != nullptr )
		{
			pErrorBlob->Release();
			pErrorBlob = nullptr;
		}

		return pShaderBlob;
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
