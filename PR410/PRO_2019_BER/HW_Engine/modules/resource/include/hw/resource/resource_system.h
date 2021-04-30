#pragma once

#include "hw/core/linked_list.h"
#include "hw/resource/resource_types.h"

namespace hw
{
	class Resource;
	struct ResourceLoadContext;

	typedef Resource*(*ResourceCreateFunc)();

	struct ResourceLoadResult
	{
		bool					isDone;
		bool					hasError;
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

		void					registerResourceType( ResourceTypeId typeId, ResourceCreateFunc createFunc, void* pContext );

		ResourceLoadContext*	beginLoadResource( const char* pResourceName );
		ResourceLoadResult		finishLoadResource( ResourceLoadContext* pContext );

		void					unloadResource( const Resource* pResource );

	private:

		struct ResourceType;
		using ResourceTypeNode = LinkedListNode< ResourceType >;

		struct ResourceType : public ResourceTypeNode
		{
			ResourceTypeId		typeId;
			ResourceCreateFunc	createFunc;
			void*				pContext;
		};

		using TypeList = LinkedList< ResourceType >;
		using LoadList = LinkedList< ResourceLoadContext >;
		using ResourceList = LinkedList< Resource >;

		const char*				m_pDataPath;

		TypeList				m_types;
		LoadList				m_loadingResources;
		ResourceList			m_resources;

		void					loadResource( ResourceLoadContext* pContext );
		bool					loadResourceFile( ResourceLoadContext* pContext );
		bool					createResource(ResourceLoadContext* pContext);
	};
}