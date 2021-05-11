#include "hw/core/string.h"

#include <string.h>

namespace hw
{
	size_t getStringSize( const char* pString )
	{
		return strlen( pString );
	}

	size_t getStringLength( const char* pString )
	{
		return 0u; // todo
	}

	size_t copyString( char* pTarget, size_t targetSize, const char* pSource )
	{
		return strcpy_s( pTarget, targetSize, pSource );
	}

	size_t appendString( char* pTarget, size_t targetSize, const char* pSource )
	{
		const size_t targetLength = getStringSize( pTarget );
		return copyString( pTarget + targetLength, targetSize - targetLength, pSource );
	}

	bool isStringEmpty( const char* pString )
	{
		return pString == nullptr ||
			pString[ 0u ] == '\0';
	}

	bool isStringEqual( const char* pString1, const char* pString2 )
	{
		return strcmp( pString1, pString2 ) == 0;
	}
}