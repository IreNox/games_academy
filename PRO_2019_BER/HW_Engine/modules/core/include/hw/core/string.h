#pragma once

namespace hw
{
	size_t		getStringSize( const char* pString );		// size in bytes
	size_t		getStringLength( const char* pString );		// length in characters

	size_t		copyString( char* pTarget, size_t targetSize, const char* pSource );
	size_t		appendString( char* pTarget, size_t targetSize, const char* pSource );

	bool		isStringEmpty( const char* pString );
	bool		isStringEqual( const char* pString1, const char* pString2 );
}