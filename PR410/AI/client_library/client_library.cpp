#include "client_library.h"

#include "client.h"

void GA_DLL runClient( const char* pUsername, DoActionCallback pCallback )
{
	GamesAcademy::Client client;
	client.run( pUsername, pCallback );
}