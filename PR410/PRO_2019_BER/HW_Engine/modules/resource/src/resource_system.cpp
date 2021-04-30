#include "hw/resource/resource_system.h"

#include "hw/resource/resource.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace hw
{
	using ResourceLoadContextNode = LinkedListNode< ResourceLoadContext >;

	struct ResourceLoadContext : public ResourceLoadContextNode
	{
		const char*		pResourceName		= nullptr;

		bool			isLoading			= true;
		bool			hasError			= false;

		void*			pResourceData		= nullptr;
		size_t			resourceDataSize	= 0u;

		Resource*		pResource			= nullptr;
	};

	ResourceSystem::ResourceSystem()
	{
	}

	ResourceSystem::~ResourceSystem()
	{
	}

	bool ResourceSystem::create( const char* pDataPath )
	{
		m_pDataPath = pDataPath;

		return true;
	}

	void ResourceSystem::destroy()
	{
	}

	void ResourceSystem::update()
	{
		for( ResourceLoadContext* pLoadContext = m_loadingResources.getFirst(); pLoadContext != nullptr; pLoadContext = m_loadingResources.getNext( pLoadContext ) )
		{
			if( !pLoadContext->isLoading )
			{
				continue;
			}

			loadResource( pLoadContext );
		}
	}

	void ResourceSystem::registerResourceType( ResourceTypeId typeId, ResourceCreateFunc createFunc, void* pContext )
	{
		ResourceType* pType = new ResourceType();
		pType->typeId		= typeId;
		pType->createFunc	= createFunc;
		pType->pContext		= pContext;

		m_types.pushBack( pType );
	}

	ResourceLoadContext* ResourceSystem::beginLoadResource( const char* pResourceName )
	{
		ResourceLoadContext* pLoadContext = new ResourceLoadContext();
		pLoadContext->pResourceName		= pResourceName;

		m_loadingResources.pushBack( pLoadContext );

		return pLoadContext;
	}

	ResourceLoadResult ResourceSystem::finishLoadResource( ResourceLoadContext* pContext )
	{
		ResourceLoadResult result = { false, false, nullptr };
		if( pContext->isLoading )
		{
			result.isDone = false;
			return result;
		}

		result.isDone		= true;
		result.hasError		= pContext->hasError;
		result.pResource	= pContext->pResource;

		m_loadingResources.remove( pContext );
		delete pContext;

		return result;
	}

	void ResourceSystem::unloadResource( const Resource* pResource )
	{
		Resource* pNonConstResource = (Resource*)pResource;
		pNonConstResource->destroy();

		m_resources.remove( pNonConstResource );
		delete pNonConstResource;
	}

	void ResourceSystem::loadResource( ResourceLoadContext* pContext )
	{
		pContext->isLoading = false;

		if( !loadResourceFile( pContext ) )
		{
			pContext->hasError = true;
			return;
		}

		if( !createResource( pContext ) )
		{
			pContext->hasError = true;
			return;
		}

		m_resources.pushBack( pContext->pResource );
	}

	bool ResourceSystem::loadResourceFile( ResourceLoadContext* pContext )
	{
		char filename[256u];
		strcpy( filename, m_pDataPath );
		const size_t dataPathLength = strlen( m_pDataPath );

		const size_t resourceNameLength = strlen( pContext->pResourceName );
		strcpy( filename + dataPathLength, pContext->pResourceName );

		strcpy( filename + dataPathLength + resourceNameLength, ".res" );

		FILE* pFileHandle = fopen( filename, "rb" );
		if( pFileHandle == nullptr )
		{
			return nullptr;
		}

		fseek(pFileHandle, 0, SEEK_END);
		fpos_t fileSize;
		fgetpos(pFileHandle, &fileSize);
		fseek(pFileHandle, 0, SEEK_SET);

		void* pMemory = malloc(fileSize);
		fread(pMemory, fileSize, 1u, pFileHandle);
		fclose(pFileHandle);

		pContext->pResourceData		= pMemory;
		pContext->resourceDataSize	= fileSize;

		return true;
	}

	bool ResourceSystem::createResource( ResourceLoadContext* pContext )
	{
		const ResourceFileHeader* pHeader = (const ResourceFileHeader*)pContext->pResourceData;
		if( pHeader->magic != ResourceFileMagic ||
			pHeader->version != ResourceFileVersion )
		{
			return false;
		}

		for( ResourceType* pType = m_types.getFirst(); pType != nullptr; pType = m_types.getNext( pType ) )
		{
			if( pType->typeId != pHeader->typeId )
			{
				continue;
			}

			const void* pResourceData = pHeader + 1u;

			Resource* pResource = pType->createFunc();
			if( !pResource->create( pContext->pResourceName, *pHeader, pResourceData, pHeader->dataSize, pType->pContext ) )
			{
				delete pResource;
				return false;
			}

			pContext->pResource = pResource;
			return true;
		}

		return false;
	}
}