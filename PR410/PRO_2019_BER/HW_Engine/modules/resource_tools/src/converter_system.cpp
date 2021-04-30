#include "hw/resource_tools/converter_system.h"

namespace hw
{
	ConverterSystem::ConverterSystem()
	{
	}

	ConverterSystem::~ConverterSystem()
	{
	}

	bool ConverterSystem::create()
	{
		return true;
	}

	void ConverterSystem::destroy()
	{
	}

	void ConverterSystem::registerConverter( ConverterBase* pConverter )
	{
	}

	void ConverterSystem::unregisterConverter( ConverterBase* pConverter )
	{
	}

	void ConverterSystem::queueFile( const char* pFilePath )
	{
	}

	bool ConverterSystem::convertAll()
	{
		return true;
	}

	bool ConverterSystem::convertFile( ConverterFile* pFile )
	{
		return true;
	}

	hw::ResourceTypeId ConverterSystem::findResourceTypeForFile( const ConverterFile* pFile )
	{
		return 0;
	}

	hw::ConverterBase* ConverterSystem::findConverterForFile( const ConverterFile* pFile )
	{
		return nullptr;
	}

}