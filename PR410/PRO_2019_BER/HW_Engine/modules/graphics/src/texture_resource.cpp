#include "hw/graphics/texture_resource.h"

#include <d3d11.h>

namespace hw
{
	TextureResource::TextureResource()
	{
	}

	TextureResource::~TextureResource()
	{
	}

	bool TextureResource::handleCreate( const void* pData, size_t dataSize, void* pContext )
	{
		TextureResourceContext* pTextureContext = (TextureResourceContext*)pContext;

		const uint32* pHeader = (const uint32*)pData;
		const uint32 width	= pHeader[ 0u ];
		const uint32 height	= pHeader[ 1u ];

		const void* pPixelData = pHeader + 2u;

		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width				= width;
		textureDesc.Height				= height;
		textureDesc.Format				= DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.ArraySize			= 1u;
		textureDesc.MipLevels			= 1u;
		textureDesc.Usage				= D3D11_USAGE_IMMUTABLE;
		textureDesc.BindFlags			= D3D11_BIND_SHADER_RESOURCE;
		textureDesc.SampleDesc.Count	= 1u;

		D3D11_SUBRESOURCE_DATA textureData;
		textureData.pSysMem		= pPixelData;
		textureData.SysMemPitch	= width * 4u;

		if( FAILED( pTextureContext->pDevice->CreateTexture2D( &textureDesc, &textureData, &m_pTexture ) ) )
		{
			return false;
		}

		if( FAILED( pTextureContext->pDevice->CreateShaderResourceView( m_pTexture, nullptr, &m_pView ) ) )
		{
			return false;
		}

		return true;
	}

	void TextureResource::handleDestroy()
	{
		if( m_pView != nullptr )
		{
			m_pView->Release();
			m_pView = nullptr;
		}

		if( m_pTexture != nullptr )
		{
			m_pTexture->Release();
			m_pTexture = nullptr;
		}
	}
}