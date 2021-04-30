#pragma once

#include "hw/core/types.h"

namespace hw
{
	static constexpr uint32 ResourceFileMagic	= 0x55574148; // HAWU
	static constexpr uint32 ResourceFileVersion = 1u;

	using ResourceTypeId = uint32;

	static constexpr ResourceTypeId TextureResourceTypeId	= 0x54584554; // TEXT
	static constexpr ResourceTypeId SoundResourceTypeId		= 0x4e554f53; // SOUN

	struct ResourceFileHeader
	{
		uint32			magic;
		uint32			version;

		ResourceTypeId	typeId;
		uint32			dataSize;
	};
}