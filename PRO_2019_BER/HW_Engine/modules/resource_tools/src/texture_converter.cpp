#include "hw/resource_tools/texture_converter.h"

#include <lodepng.h>

namespace hw
{
	ResourceTypeId TextureConverter::getTypeId()
	{
		return TextureResourceTypeId;
	}

	bool TextureConverter::convertResource( ConvertContext* pContext )
	{
		unsigned char* pPixelData = nullptr;
		unsigned width = 0;
		unsigned height = 0;
		if( lodepng_decode32( &pPixelData, &width, &height, (const unsigned char*)pContext->pSourceData, pContext->sourceDataSize ) != 0 )
		{
			return false;
		}

		const size_t imageSize = width * height * 4u;
		const size_t resourceSize = (sizeof( uint32 ) * 2u) + imageSize;
		void* pResourceData = malloc( resourceSize );

		uint32* pHeader = (uint32*)pResourceData;
		pHeader[ 0u ] = width;
		pHeader[ 1u ] = height;

		void* pTargetData = pHeader + 2u;
		memcpy( pTargetData, pPixelData, imageSize );

		pContext->pResourceData		= pResourceData;
		pContext->resourceDataSize	= resourceSize;

		return true;
	}
}
