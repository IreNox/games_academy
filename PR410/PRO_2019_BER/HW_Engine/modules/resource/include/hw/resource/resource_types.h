#pragma once

#include "hw/core/types.h"

namespace hw
{
	static constexpr uint32 ResourceFileMagic	= 0x48415755; // HAWU
	static constexpr uint32 ResourceFileVersion = 1u;

	using ResourceTypeId = uint32;

	struct ResourceFileHeader
	{
		uint32			magic;
		uint32			version;

		ResourceTypeId	typeId;
		uint32			dataSize;
	};
}