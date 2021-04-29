#pragma once

#include "hw/core/linked_list.h"
#include "hw/resource/resource_types.h"

namespace hw
{
	class Resource;
	using ResourceNode = LinkedListNode< Resource >;

	class Resource : ResourceNode
	{
	public:

						Resource();
		virtual			~Resource();

		bool			create( const char* pName, const ResourceFileHeader& header, const void* pData, size_t dataSize );
		void			destroy();

		const char*		getName() const { return m_pName; }
		ResourceTypeId	getType() const { return m_type; }

	private:

		const char*		m_pName	= nullptr;
		uint32			m_type	= 0;

		virtual bool	handleCreate( const void* pData, size_t dataSize ) = 0;
		virtual void	handleDestroy() = 0;
	};
}