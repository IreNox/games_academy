#include "hw/resource_tools/converter_system.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

namespace hw
{
	ConverterSystem::ConverterSystem()
	{
	}

	ConverterSystem::~ConverterSystem()
	{
	}

	bool ConverterSystem::create( const char* pOutputPath )
	{
		m_pOutputPath = pOutputPath;

		return true;
	}

	void ConverterSystem::destroy()
	{
	}

	void ConverterSystem::registerConverter( ConverterBase* pConverter )
	{
		m_converters.pushBack( pConverter );
	}

	void ConverterSystem::unregisterConverter( ConverterBase* pConverter )
	{
		m_converters.remove( pConverter );
	}

	void ConverterSystem::queueFile( const char* pFilePath )
	{
		ConverterFile* pFile = new ConverterFile();
		pFile->pFilePath = pFilePath;

		m_files.pushBack( pFile );
	}

	bool ConverterSystem::convertAll()
	{
		bool ok = true;
		for( ConverterFile* pFile = m_files.getFirst(); pFile != nullptr; pFile = m_files.getNext( pFile ) )
		{
			ok &= convertFile( pFile );
		}

		return ok;
	}

	bool ConverterSystem::convertFile( ConverterFile* pFile )
	{
		ConverterBase* pConverter = findConverterForFile( pFile );
		if( pConverter == nullptr )
		{
			return false;
		}

		ConvertContext* pContext = &pFile->context;
		pContext->typeId = pConverter->getTypeId();

		if( !readSourceFile( pFile ) )
		{
			return false;
		}

		if( !pConverter->convertResource( pContext ) )
		{
			return false;
		}

		if( !writeResourceData( pFile ) )
		{
			return false;
		}

		return true;
	}

	ResourceTypeId ConverterSystem::findResourceTypeForFile( const ConverterFile* pFile )
	{
		const size_t filePathLength = strlen( pFile->pFilePath );

		const char* pExtension = strrchr( pFile->pFilePath, '.' );
		if( pExtension == nullptr )
		{
			return 0u;
		}

		if( strcmp( pExtension, ".png" ) == 0 )
		{
			return TextureResourceTypeId;
		}
		else if (strcmp(pExtension, ".wav") == 0)
		{
			return SoundResourceTypeId;
		}

		return 0;
	}

	ConverterBase* ConverterSystem::findConverterForFile( const ConverterFile* pFile )
	{
		const ResourceTypeId typeId = findResourceTypeForFile( pFile );
		if( typeId == 0u )
		{
			return nullptr;
		}

		for( ConverterBase* pConverter = m_converters.getFirst(); pConverter != nullptr; pConverter = m_converters.getNext( pConverter ) )
		{
			if( pConverter->getTypeId() == typeId )
			{
				return pConverter;
			}
		}

		return nullptr;
	}

	bool ConverterSystem::readSourceFile( ConverterFile* pFile )
	{
		FILE* pFileHandle = fopen( pFile->pFilePath, "rb" );
		if( pFileHandle == nullptr )
		{
			return false;
		}

		fseek( pFileHandle, 0, SEEK_END );
		fpos_t fileSize;
		fgetpos( pFileHandle, &fileSize );
		fseek( pFileHandle, 0, SEEK_SET );

		void* pMemory = malloc( fileSize );
		fread( pMemory, fileSize, 1u, pFileHandle );
		fclose( pFileHandle );

		pFile->context.pSourceData		= pMemory;
		pFile->context.sourceDataSize	= fileSize;

		return true;
	}

	bool ConverterSystem::writeResourceData( ConverterFile* pFile )
	{
		char filename[ 256u ];
		strcpy( filename, m_pOutputPath );
		const size_t outputPathLength = strlen( m_pOutputPath );

		const char* pExtension = strrchr( pFile->pFilePath, '.' );
		if( pExtension == nullptr )
		{
			return 0u;
		}

		const char* pBasename = strrchr( pFile->pFilePath, '\\' );
		if( pBasename == nullptr )
		{
			return 0u;
		}
		pBasename++;

		const size_t basenameLength = pExtension - pBasename;
		memcpy( filename + outputPathLength, pBasename, basenameLength );
		strcpy( filename + outputPathLength + basenameLength, ".res" );

		FILE* pFileHandle = fopen( filename, "wb" );
		if( pFileHandle == nullptr )
		{
			return false;
		}

		ResourceFileHeader header;
		header.magic	= ResourceFileMagic;
		header.version	= ResourceFileVersion;
		header.typeId	= pFile->context.typeId;
		header.dataSize	= pFile->context.resourceDataSize;

		fwrite( &header, sizeof( header ), 1u, pFileHandle );
		fwrite( pFile->context.pResourceData, pFile->context.resourceDataSize, 1u, pFileHandle );
		fclose( pFileHandle );

		return true;
	}
}