#include "hw/graphics/graphics_system.h"

#include <d3dcompiler.h>

namespace hw
{
	static constexpr int	WindowWidth = 1280;
	static constexpr int	WindowHeight = 720;

	static const wchar_t*	s_pWindowTitle = L"CS310 - Input";

	struct GraphicsVertexConstantData
	{
		float		projection[ 4u ][ 4u ];
	};

	bool GraphicsSystem::create()
	{
		const HINSTANCE	hInstance = GetModuleHandle(nullptr);

		WNDCLASSEXW windowClass = {};
		windowClass.cbSize = sizeof(WNDCLASSEXW);
		windowClass.hInstance = hInstance;
		windowClass.lpfnWndProc = &GraphicsSystem::windowProc;
		windowClass.lpszClassName = L"GAWindowClass";
		windowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
		windowClass.hCursor = LoadCursor(nullptr, IDC_ARROW);

		HRESULT result = RegisterClassExW(&windowClass);
		if (FAILED(result))
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

		if (m_windowHandle == nullptr)
		{
			return false;
		}

		SetWindowLongPtr(m_windowHandle, GWLP_USERDATA, (LONG_PTR)this);

		ShowWindow(m_windowHandle, SW_SHOWNORMAL);
		UpdateWindow(m_windowHandle);

		RECT clientRect;
		GetClientRect(m_windowHandle, &clientRect);

		m_isOpen = true;
		m_width = (clientRect.right - clientRect.left);
		m_height = (clientRect.bottom - clientRect.top);

		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
		swapChainDesc.BufferCount = 2u;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.Width = m_width;
		swapChainDesc.BufferDesc.Height = m_height;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = m_windowHandle;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.Windowed = TRUE;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

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

		if (FAILED(result))
		{
			destroy();
			return false;
		}

		ID3D11Texture2D* pBackBuffer = nullptr;
		if (FAILED(m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&pBackBuffer)))
		{
			destroy();
			return false;
		}

		if (FAILED(m_pDevice->CreateRenderTargetView(pBackBuffer, nullptr, &m_pBackBufferView)))
		{
			pBackBuffer->Release();
			destroy();
			return false;
		}

		pBackBuffer->Release();

		if (!createResources())
		{
			destroy();
			return false;
		}

		return true;
	}

	void GraphicsSystem::destroy()
	{
		destroyResources();

		if (m_pBackBufferView != nullptr)
		{
			m_pBackBufferView->Release();
			m_pBackBufferView = nullptr;
		}

		if (m_pContext != nullptr)
		{
			m_pContext->Release();
			m_pContext = nullptr;
		}

		if (m_pDevice != nullptr)
		{
			m_pDevice->Release();
			m_pDevice = nullptr;
		}

		if (m_pSwapChain != nullptr)
		{
			m_pSwapChain->Release();
			m_pSwapChain = nullptr;
		}

		if (m_windowHandle != nullptr)
		{
			DestroyWindow(m_windowHandle);
			m_windowHandle = nullptr;
		}
	}

	void GraphicsSystem::update()
	{
		MSG msg;
		while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	ID3D11DeviceContext* GraphicsSystem::beginFrame( const float backgroundColor[ 4u ] )
	{
		D3D11_MAPPED_SUBRESOURCE mapData;
		m_pContext->Map( m_pConstantBuffer, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &mapData );

		GraphicsVertexConstantData* pConstantData = (GraphicsVertexConstantData*)mapData.pData;

		pConstantData->projection[	0u	][	0u	] = 2.0f / float( m_width );
		pConstantData->projection[	1u	][	0u	] = 0.0f;
		pConstantData->projection[	2u	][	0u	] = 0.0f;
		pConstantData->projection[	3u	][	0u	] = 0.0f;

		pConstantData->projection[	0u	][	1u	] = 0.0f;
		pConstantData->projection[	1u	][	1u	] = 2.0f / -float( m_height );
		pConstantData->projection[	2u	][	1u	] = 0.0f;
		pConstantData->projection[	3u	][	1u	] = 0.0f;

		pConstantData->projection[	0u	][	2u	] = 0.0f;
		pConstantData->projection[	1u	][	2u	] = 0.0f;
		pConstantData->projection[	2u	][	2u	] = 1.0f / (0.0f - 1.0f);
		pConstantData->projection[	3u	][	2u	] = 0.0f;

		pConstantData->projection[	0u	][	3u	] = -1.0f;
		pConstantData->projection[	1u	][	3u	] = 1.0f;
		pConstantData->projection[	2u	][	3u	] = 0.0f;
		pConstantData->projection[	3u	][	3u	] = 1.0f;

		m_pContext->Unmap( m_pConstantBuffer, 0u );

		m_pContext->ClearRenderTargetView(m_pBackBufferView, backgroundColor);

		m_pContext->OMSetRenderTargets(1u, &m_pBackBufferView, nullptr);

		D3D11_VIEWPORT viewport = {};
		viewport.Width = (float)m_width;
		viewport.Height = (float)m_height;
		viewport.MaxDepth = 1.0f;

		m_pContext->RSSetViewports(1u, &viewport);

		m_pContext->IASetInputLayout(m_pVertexLayout);
		m_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		m_pContext->VSSetShader(m_pVertexShader, nullptr, 0u);
		m_pContext->PSSetShader(m_pPixelShader, nullptr, 0u);

		m_pContext->VSSetConstantBuffers( 0u, 1u, &m_pConstantBuffer );

		return m_pContext;
	}

	void GraphicsSystem::endFrame()
	{
		m_pSwapChain->Present(1, 0);
	}

	void GraphicsSystem::draw( const GameVertex* pVertives, UINT vertexCount )
	{
		D3D11_MAPPED_SUBRESOURCE bufferData;
		m_pContext->Map( m_pVertexBuffer, 0u, D3D11_MAP_WRITE_DISCARD, 0u, &bufferData );

		memcpy( bufferData.pData, pVertives, sizeof( GameVertex ) * vertexCount );

		m_pContext->Unmap( m_pVertexBuffer, 0u );

		UINT stride = sizeof( GameVertex );
		UINT offset = 0u;
		m_pContext->IASetVertexBuffers( 0u, 1u, &m_pVertexBuffer, &stride, &offset );

		m_pContext->Draw( vertexCount, 0u );
	}

	bool GraphicsSystem::createResources()
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

			cbuffer constants : register(b0)
			{
				float4x4	proj;
			};

			VertexToPixel main( VertexInput input )
			{
				float4 position = float4( input.position, 1.0 );
				position = mul( position, proj );

				VertexToPixel output;
				output.position	= position;
				output.color	= input.color;

				return output;
			}
		)V0G0N";

		ID3DBlob* pVertexShaderBlob = compileShader(pVertexShader, "vs_5_0");
		if (pVertexShaderBlob == nullptr)
		{
			return false;
		}

		HRESULT result = m_pDevice->CreateVertexShader(pVertexShaderBlob->GetBufferPointer(), pVertexShaderBlob->GetBufferSize(), nullptr, &m_pVertexShader);
		if (FAILED(result))
		{
			pVertexShaderBlob->Release();
			return false;
		}

		const D3D11_INPUT_ELEMENT_DESC inputElements[] =
		{
			{ "POSITION",	0u,	DXGI_FORMAT_R32G32B32_FLOAT,	0u,	D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0u },
			{ "COLOR",		0u, DXGI_FORMAT_R32G32B32A32_FLOAT,	0u, D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0u }
		};

		result = m_pDevice->CreateInputLayout( inputElements, ARRAY_COUNT( inputElements ), pVertexShaderBlob->GetBufferPointer(), pVertexShaderBlob->GetBufferSize(), &m_pVertexLayout );
		pVertexShaderBlob->Release();

		if (FAILED(result))
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

		ID3DBlob* pPixelShaderBlob = compileShader(pPixelShader, "ps_5_0");
		if (pPixelShaderBlob == nullptr)
		{
			return false;
		}

		result = m_pDevice->CreatePixelShader(pPixelShaderBlob->GetBufferPointer(), pPixelShaderBlob->GetBufferSize(), nullptr, &m_pPixelShader);
		pPixelShaderBlob->Release();
		if (FAILED(result))
		{
			return false;
		}

		D3D11_BUFFER_DESC vertexBuferDesc = {};
		vertexBuferDesc.ByteWidth		= sizeof( GameVertex ) * 128u;
		vertexBuferDesc.Usage			= D3D11_USAGE_DYNAMIC;
		vertexBuferDesc.BindFlags		= D3D11_BIND_VERTEX_BUFFER;
		vertexBuferDesc.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;

		if( FAILED( m_pDevice->CreateBuffer( &vertexBuferDesc, nullptr, &m_pVertexBuffer ) ) )
		{
			return false;
		}

		D3D11_BUFFER_DESC constantBufferDesc = {};
		constantBufferDesc.ByteWidth		= sizeof( GraphicsVertexConstantData );
		constantBufferDesc.Usage			= D3D11_USAGE_DYNAMIC;
		constantBufferDesc.BindFlags		= D3D11_BIND_CONSTANT_BUFFER;
		constantBufferDesc.CPUAccessFlags	= D3D11_CPU_ACCESS_WRITE;

		if( FAILED( m_pDevice->CreateBuffer( &constantBufferDesc, nullptr, &m_pConstantBuffer) ) )
		{
			return false;
		}

		return true;
	}

	void GraphicsSystem::destroyResources()
	{
		if (m_pConstantBuffer != nullptr)
		{
			m_pConstantBuffer->Release();
			m_pConstantBuffer = nullptr;
		}

		if (m_pVertexBuffer != nullptr)
		{
			m_pVertexBuffer->Release();
			m_pVertexBuffer = nullptr;
		}

		if (m_pVertexLayout != nullptr)
		{
			m_pVertexLayout->Release();
			m_pVertexLayout = nullptr;
		}

		if (m_pPixelShader != nullptr)
		{
			m_pPixelShader->Release();
			m_pPixelShader = nullptr;
		}

		if (m_pVertexShader != nullptr)
		{
			m_pVertexShader->Release();
			m_pVertexShader = nullptr;
		}
	}

	ID3DBlob* GraphicsSystem::compileShader(const char* pShaderText, const char* pTarget)
	{
		ID3DBlob* pShaderBlob = nullptr;
		ID3DBlob* pErrorBlob = nullptr;

		UINT flags = 0;
#ifdef _DEBUG
		flags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#endif
		HRESULT result = D3DCompile(pShaderText, strlen(pShaderText), "Shader", nullptr, nullptr, "main", pTarget, flags, 0, &pShaderBlob, &pErrorBlob);
		if (FAILED(result))
		{
			MessageBoxA(m_windowHandle, (const char*)pErrorBlob->GetBufferPointer(), "DirectX", MB_ICONSTOP);

			pErrorBlob->Release();
			return nullptr;
		}

		if (pErrorBlob != nullptr)
		{
			pErrorBlob->Release();
			pErrorBlob = nullptr;
		}

		return pShaderBlob;
	}

	LRESULT CALLBACK GraphicsSystem::windowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
	{
		GraphicsSystem* pGraphics = (GraphicsSystem*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
		if (pGraphics != nullptr &&
			pGraphics->handleMessage(message, wParam))
		{
			return 0u;
		}

		switch (message)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}

		return 0;
	}

	bool GraphicsSystem::handleMessage(unsigned int messageCode, size_t wParam)
	{
		switch (messageCode)
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