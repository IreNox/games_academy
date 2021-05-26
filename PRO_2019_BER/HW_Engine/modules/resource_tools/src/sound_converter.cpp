#include "hw/resource_tools/sound_converter.h"

namespace hw
{
	ResourceTypeId SoundConverter::getTypeId()
	{
		return SoundResourceTypeId;
	}

	bool SoundConverter::convertResource( ConvertContext* pContext )
	{
		return true;
	}
}
