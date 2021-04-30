#include "hw/resource/resource.h"

namespace hw
{
	Resource::Resource()
	{
	}

	Resource::~Resource()
	{
	}

	bool Resource::create(const char* pName, const ResourceFileHeader& header, const void* pData, size_t dataSize)
	{
		m_pName = pName;
		m_type	= header.typeId;

		return handleCreate( pData, dataSize );
	}

	void Resource::destroy()
	{
		handleDestroy();

		m_type	= 0u;
		m_pName	= nullptr;
	}
}
