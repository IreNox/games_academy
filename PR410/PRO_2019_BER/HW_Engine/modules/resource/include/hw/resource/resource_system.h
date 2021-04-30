#pragma once

#include "hw/core/linked_list.h"

namespace hw
{
	class Resource;
	struct ResourceLoadContext;

	struct ResourceLoadResult
	{
		bool					ok;
		const Resource*			pResource;
	};

	class ResourceSystem
	{
	public:

								ResourceSystem();
								~ResourceSystem();

		bool					create( const char* pDataPath );
		void					destroy();

		void					update();

		ResourceLoadContext*	beginLoadResource( const char* pResourceName );
		ResourceLoadResult		finishLoadResource( ResourceLoadContext* pContext );

		void					unloadResource( const Resource* pResource );

	private:

		using LoadList = LinkedList< ResourceLoadContext >;
		using ResourceList = LinkedList< Resource >;

		const char*				m_pDataPath;

		LoadList				m_loadingResources;
		ResourceList			m_resource;
	};
}