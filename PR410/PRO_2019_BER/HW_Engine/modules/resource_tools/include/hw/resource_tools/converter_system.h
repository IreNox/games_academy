#pragma once

#include "hw/resource_tools/converter_base.h"

namespace hw
{
	struct ConverterFile;
	using ConverterFileNode = LinkedListNode< ConverterFile >;

	struct ConverterFile : ConverterFileNode
	{
		const char*		pFilePath;

		ConvertContext	context;
	};

	class ConverterSystem
	{
	public:

						ConverterSystem();
						~ConverterSystem();

		bool			create( const char* pOutputPath );
		void			destroy();

		void			registerConverter( ConverterBase* pConverter );
		void			unregisterConverter( ConverterBase* pConverter );

		void			queueFile( const char* pFilePath );

		bool			convertAll();

	private:

		using ConverterList = LinkedList< ConverterBase >;
		using FileList = LinkedList< ConverterFile >;

		const char*		m_pOutputPath	= nullptr;

		ConverterList	m_converters;
		FileList		m_files;

		bool			convertFile( ConverterFile* pFile );

		ResourceTypeId	findResourceTypeForFile( const ConverterFile* pFile );
		ConverterBase*	findConverterForFile( const ConverterFile* pFile );

		bool			readSourceFile( ConverterFile* pFile );
		bool			writeResourceData( ConverterFile* pFile );
	};
}