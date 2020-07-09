#include "../client_library/client_library.h"

#include <windows.h>

uint8_t doAction( const GameState* pGameState, void* pUserData )
{
	//return pGameState->round % (PlayerActionType_ShootDownRight + 1);
	return PlayerActionType_Invalid;
}

int __stdcall WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd )
{
	runClient( "MyName", doAction, nullptr );
	return 0;
}
