#pragma once

#include "hw/core/linked_list.h"
#include "hw/resource/resource_types.h"

namespace hw
{
	class Resource;
	using ResourceNode = LinkedListNode< Resource >;

	class Resource : public ResourceNode
	{
	public:

						Resource();
		virtual			~Resource();

		bool			create( const char* pName, const ResourceFileHeader& header, const void* pData, size_t dataSize, void* pContext );
		void			destroy();

		const char*		getName() const { return m_pName; }
		ResourceTypeId	getType() const { return m_type; }

	protected:

		virtual bool	handleCreate( const void* pData, size_t dataSize, void* pContext ) = 0;
		virtual void	handleDestroy() = 0;

	private:

		const char*		m_pName	= nullptr;
		uint32			m_type	= 0;
	};
}