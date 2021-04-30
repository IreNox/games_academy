#include "hw/resource/resource_system.h"

namespace hw
{
	ResourceSystem::ResourceSystem()
	{
	}

	ResourceSystem::~ResourceSystem()
	{
	}

	bool ResourceSystem::create( const char* pDataPath )
	{
		return true;
	}

	void ResourceSystem::destroy()
	{
	}

	void ResourceSystem::update()
	{
	}

	ResourceLoadContext* ResourceSystem::beginLoadResource( const char* pResourceName )
	{
		return nullptr;
	}

	ResourceLoadResult ResourceSystem::finishLoadResource( ResourceLoadContext* pContext )
	{
		const ResourceLoadResult result = { true, nullptr };
		return result;
	}

	void ResourceSystem::unloadResource( const Resource* pResource )
	{
	}
}