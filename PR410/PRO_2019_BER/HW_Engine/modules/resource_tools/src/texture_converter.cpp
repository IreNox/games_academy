#include "hw/resource_tools/texture_converter.h"

namespace hw
{
	ResourceTypeId TextureConverter::getTypeId()
	{
		return TextureResourceTypeId;
	}

	bool TextureConverter::convertResource( ConvertContext* pContext )
	{
		return true;
	}
}
