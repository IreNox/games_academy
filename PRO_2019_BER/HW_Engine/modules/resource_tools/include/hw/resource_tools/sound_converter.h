#pragma once

#include "hw/resource_tools/converter_base.h"

namespace hw
{
	class SoundConverter : public ConverterBase
	{
	public:

		virtual ResourceTypeId	getTypeId() override final;

		virtual bool			convertResource( ConvertContext* pContext ) override final;
	};
}