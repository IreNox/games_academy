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

		bool			create();
		void			destroy();

		void			registerConverter( ConverterBase* pConverter );
		void			unregisterConverter( ConverterBase* pConverter );

		void			queueFile( const char* pFilePath );

		bool			convertAll();

	private:

		using ConverterList = LinkedList< ConverterBase >;
		using FileList = LinkedList< ConverterFile >;

		ConverterList	m_converters;
		FileList		m_files;

		bool			convertFile( ConverterFile* pFile );

		ResourceTypeId	findResourceTypeForFile( const ConverterFile* pFile );
		ConverterBase*	findConverterForFile( const ConverterFile* pFile );
	};
}