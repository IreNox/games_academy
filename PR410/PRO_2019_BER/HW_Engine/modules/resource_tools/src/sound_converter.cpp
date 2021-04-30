#include "hw/resource_tools/sound_converter.h"

namespace hw
{
	ResourceTypeId SoundConverter::getTypeId()
	{
		return 0x534f554e; // SOUN
	}

	bool SoundConverter::convertResource( ConvertContext* pContext )
	{
		return true;
	}
}
