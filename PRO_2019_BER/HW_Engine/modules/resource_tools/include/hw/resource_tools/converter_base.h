#pragma once

#include "hw/core/linked_list.h"
#include "hw/resource/resource_types.h"

namespace hw
{
	struct ConvertContext
	{
		// in
		const void*		pSourceData;
		size_t			sourceDataSize;
		ResourceTypeId	typeId;

		// out
		void*			pResourceData;
		size_t			resourceDataSize;
	};

	class ConverterBase;
	using ConverterBaseNode = LinkedListNode< ConverterBase >;

	class ConverterBase : public ConverterBaseNode
	{
	public:

		virtual ResourceTypeId	getTypeId() = 0;

		virtual bool			convertResource( ConvertContext* pContext ) = 0;
	};
}