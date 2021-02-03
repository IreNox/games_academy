#include "SampleTexture.hpp"

#include "../01-Window/SampleDevice.hpp"
#include "../01-Window/SampleTypes.hpp"
#include "../01-Window/SampleWindow.hpp"

#include "SampleFilesystem.hpp"

#include <DDSTextureLoader/DDSTextureLoader.h>
#include <LodePNG/lodepng.h>
#include <LodePNG/lodepng_util.h>
#include <d3d11.h>

#include <assert.h>

namespace GamesAcademy
{
	static bool isPng( const char* pString )
	{
		if( pString == nullptr )
		{
			return false;
		}

		const size_t stringLength = strlen( pString );
		if( stringLength < 4u )
		{
			return false;
		}

		return pString[ stringLength - 4 ] == '.' &&
			pString[stringLength - 3] == 'p' &&
			pString[stringLength - 2] == 'n' &&
			pString[stringLength - 1] == 'g';
	}

	static void convertPixelData( const uint8* pSourceData, size_t sourceDataSize, uint8* pTargetData, size_t targetDataSize, size_t width, size_t height, bool rgbToRgba, bool isGrayscale, bool is16Bit )
	{
		const size_t pixelCount		= width * height;
		const size_t colorSize		= (is16Bit ? 2u : 1u);
		const size_t channelCount	= (isGrayscale ? 1u : 4u);
		if( rgbToRgba )
		{
			const size_t sourcePixelSize	= colorSize * 3u;
			const uint8* pSourcePixel		= pSourceData;

			const size_t targetPixelSize	= colorSize * 4u;
			uint8* pTargetPixel				= pTargetData;

			for( size_t i = 0u; i < pixelCount; ++i )
			{
				memcpy( pTargetPixel, pSourcePixel, sourcePixelSize );
				memset( pTargetPixel + (3u * colorSize), 0xff, colorSize );

				pSourcePixel += sourcePixelSize;
				pTargetPixel += targetPixelSize;
			}
		}
		else
		{
			memcpy( pTargetData, pSourceData, sourceDataSize );
		}

		if( is16Bit && false )
		{
			// change endianness
			uint8* pTargetColor = pTargetData;

			const size_t colorCount = pixelCount * channelCount;
			for( size_t i = 0u; i < colorCount; ++i )
			{
				const uint8 color1 = pTargetColor[ 0u ];
				const uint8 color2 = pTargetColor[ 1u ];

				pTargetColor[ 0u ] = color2;
				pTargetColor[ 1u ] = color1;

				pTargetColor += 2u;
			}
		}
	}

	SampleTexture::SampleTexture()
	{
	}

	SampleTexture::~SampleTexture()
	{
		destroy();
	}

	bool SampleTexture::createFromFile( SampleDevice& device, SampleFilesystem& filesystem, const char* pFilename )
	{
		MemoryBlock fileData = filesystem.readFile( pFilename );
		if( fileData.pData == nullptr )
		{
			return false;
		}

		if( isPng( pFilename ) )
		{
			LodePNGState state;
			lodepng_state_init( &state );

			unsigned width;
			unsigned height;
			if( lodepng_inspect( &width, &height, &state, (const unsigned char*)fileData.pData, fileData.size ) != 0u )
			{
				device.getWindow().showMessageBox( L"Failed to read PNG File." );
				lodepng_state_cleanup( &state );
				filesystem.freeFile( fileData );
				return false;
			}

			D3D11_TEXTURE2D_DESC textureDesc = {};
			textureDesc.Width				= width;
			textureDesc.Height				= height;
			textureDesc.ArraySize			= 1u;
			textureDesc.MipLevels			= 1u;
			textureDesc.Usage				= D3D11_USAGE_IMMUTABLE;
			textureDesc.BindFlags			= D3D11_BIND_SHADER_RESOURCE;
			textureDesc.SampleDesc.Count	= 1u;

			size_t sourceMemorySize;
			size_t textureMemorySize;
			const size_t bitDepth = state.info_png.color.bitdepth;
			const size_t colorSize = bitDepth / 8u;
			if( state.info_png.color.colortype == LCT_RGB ||
			    state.info_png.color.colortype == LCT_RGBA )
			{
				if( bitDepth == 8u )
				{
					textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
				}
				else if( bitDepth == 16u )
				{
					textureDesc.Format = DXGI_FORMAT_R16G16B16A16_UNORM;
				}

				textureMemorySize = width * height * 4u * colorSize;

				if( state.info_png.color.colortype == LCT_RGB )
				{
					sourceMemorySize = width * height * 3u * colorSize;
				}
				else
				{
					sourceMemorySize = textureMemorySize;
				}
			}
			else if( state.info_png.color.colortype == LCT_GREY )
			{
				if( bitDepth == 8u )
				{
					textureDesc.Format = DXGI_FORMAT_R8_UNORM;
				}
				else if( bitDepth == 16u )
				{
					textureDesc.Format = DXGI_FORMAT_R16G16_UNORM;
				}

				textureMemorySize = width * height * 1u * 4u;
				sourceMemorySize = textureMemorySize;
			}

			if( textureDesc.Format == DXGI_FORMAT_UNKNOWN )
			{
				device.getWindow().showMessageBox( L"Unsupported PNG format." );
				lodepng_state_cleanup( &state );
				filesystem.freeFile( fileData );
				return false;
			}

			uint8* pPixelData = nullptr;
			if( lodepng_decode( &pPixelData, &width, &height, &state, (const unsigned char*)fileData.pData, fileData.size ) != 0 )
			{
				device.getWindow().showMessageBox( L"Failed to decode PNG file." );
				lodepng_state_cleanup( &state );
				filesystem.freeFile( fileData );
				return false;
			}
			filesystem.freeFile( fileData );

			uint8* pTextureData = (uint8*)malloc( textureMemorySize );
			{
				const bool rgbToRgba = (state.info_png.color.colortype == LCT_RGB);
				const bool isGrayscale = (state.info_png.color.colortype == LCT_GREY);
				const bool is16Bit = (state.info_png.color.bitdepth == 16u);
				convertPixelData( pPixelData, sourceMemorySize, pTextureData, textureMemorySize, width, height, rgbToRgba, isGrayscale, is16Bit );
			}

			D3D11_SUBRESOURCE_DATA textureData;
			textureData.pSysMem		= pTextureData;
			textureData.SysMemPitch	= UINT( textureMemorySize / height );

			HRESULT result = device.getDevice()->CreateTexture2D( &textureDesc, &textureData, &m_pTexture );
			free( pPixelData );
			lodepng_state_cleanup( &state );

			if( FAILED( result ) )
			{
				device.getWindow().showMessageBox( L"Failed to create Texture." );
				return false;
			}

			result = device.getDevice()->CreateShaderResourceView( m_pTexture, nullptr, &m_pShaderResourceView );
			if( FAILED( result ) )
			{
				destroy();
				device.getWindow().showMessageBox( L"Failed to create Texture." );
				return false;
			}
		}
		else
		{
			const HRESULT result = DirectX::CreateDDSTextureFromMemory( device.getDevice(), (const uint8*)fileData.pData, fileData.size, (ID3D11Resource**)&m_pTexture, &m_pShaderResourceView );
			filesystem.freeFile( fileData );

			if( FAILED( result ) )
			{
				device.getWindow().showMessageBox( L"Failed to load Texture." );
				return false;
			}
		}

		D3D11_TEXTURE2D_DESC desc;
		m_pTexture->GetDesc( &desc );

		m_width			= uint16( desc.Width );
		m_height		= uint16( desc.Height );

		m_pDevice		= &device;
		m_pFilesystem	= &filesystem;
		m_pFileWatch	= filesystem.startWatchFile( pFilename );

		return true;
	}

	bool SampleTexture::createEmptyShadowMap( SampleDevice& device, uint16 width, uint16 height )
	{
		m_width		= width;
		m_height	= height;

		D3D11_TEXTURE2D_DESC textureDesc = {};
		textureDesc.Width				= width;
		textureDesc.Height				= height;
		textureDesc.MipLevels			= 1u;
		textureDesc.ArraySize			= 1u;
		textureDesc.Format				= DXGI_FORMAT_R16_TYPELESS;
		textureDesc.SampleDesc.Count	= 1u;
		textureDesc.Usage				= D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags			= D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;

		HRESULT result = device.getDevice()->CreateTexture2D( &textureDesc, nullptr, &m_pTexture );
		if( FAILED( result ) )
		{
			device.getWindow().showMessageBox( L"Failed to create Shadow Map." );
			return false;
		}

		D3D11_SHADER_RESOURCE_VIEW_DESC shaderView = {};
		shaderView.Format				= DXGI_FORMAT_R16_UNORM;
		shaderView.ViewDimension		= D3D11_SRV_DIMENSION_TEXTURE2D;
		shaderView.Texture2D.MipLevels	= 1u;

		result = device.getDevice()->CreateShaderResourceView( m_pTexture, &shaderView, &m_pShaderResourceView );
		if( FAILED( result ) )
		{
			device.getWindow().showMessageBox( L"Failed to create Shadow Map Shader View." );
			return false;
		}

		D3D11_DEPTH_STENCIL_VIEW_DESC depthView = {};
		depthView.Format				= DXGI_FORMAT_D16_UNORM;
		depthView.ViewDimension			= D3D11_DSV_DIMENSION_TEXTURE2D;

		result = device.getDevice()->CreateDepthStencilView( m_pTexture, &depthView, &m_pDepthStencilView );
		if( FAILED( result ) )
		{
			device.getWindow().showMessageBox( L"Failed to create Shadow Map Render Target View." );
			return false;
		}

		return true;
	}

	void SampleTexture::destroy()
	{
		if( m_pFileWatch != nullptr )
		{
			m_pFilesystem->stopWatchFile( m_pFileWatch );
			m_pFileWatch = nullptr;
		}

		if( m_pDepthStencilView != nullptr )
		{
			m_pDepthStencilView->Release();
			m_pDepthStencilView = nullptr;
		}

		if( m_pShaderResourceView != nullptr )
		{
			m_pShaderResourceView->Release();
			m_pShaderResourceView = nullptr;
		}

		if( m_pTexture != nullptr )
		{
			m_pTexture->Release();
			m_pTexture = nullptr;
		}

		m_height		= 0u;
		m_width			= 0u;
		m_pFilesystem	= nullptr;
		m_pDevice		= nullptr;
	}

	void SampleTexture::applyToDomainShader( ID3D11DeviceContext* pContext, size_t slotIndex )
	{
		checkForChanges();

		pContext->DSSetShaderResources( UINT( slotIndex ), 1u, &m_pShaderResourceView );
	}

	void SampleTexture::applyToPixelShader( ID3D11DeviceContext* pContext, size_t slotIndex )
	{
		checkForChanges();

		pContext->PSSetShaderResources( UINT( slotIndex ), 1u, &m_pShaderResourceView );
	}

	void SampleTexture::applyRenderTargetAndClear( ID3D11DeviceContext* pContext )
	{
		pContext->ClearDepthStencilView( m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0u );
		pContext->OMSetRenderTargets( 0u, nullptr, m_pDepthStencilView );

		D3D11_VIEWPORT viewport = {};
		viewport.Width		= (float)m_width;
		viewport.Height		= (float)m_height;
		viewport.MaxDepth	= 1.0f;
		pContext->RSSetViewports( 1u, &viewport );
	}

	void SampleTexture::checkForChanges()
	{
		if( !m_pFilesystem->hasWatchedFileChanged( m_pFileWatch ) )
		{
			return;
		}

		ID3D11Texture2D* pTextureBackup			= m_pTexture;
		ID3D11ShaderResourceView* pViewBackup	= m_pShaderResourceView;

		if( createFromFile( *m_pDevice, *m_pFilesystem, m_pFilesystem->getWatchedFileName( m_pFileWatch ) ) )
		{
			pViewBackup->Release();
			pTextureBackup->Release();
		}
		else
		{
			m_pTexture				= pTextureBackup;
			m_pShaderResourceView	= pViewBackup;
		}
	}
}
