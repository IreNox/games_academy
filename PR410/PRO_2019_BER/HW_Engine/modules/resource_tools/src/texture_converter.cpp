#include "hw/resource_tools/texture_converter.h"

namespace hw
{
	ResourceTypeId TextureConverter::getTypeId()
	{
		return 0x54455854; // TEXT
	}

	bool TextureConverter::convertResource( ConvertContext* pContext )
	{
		return true;
	}
}
