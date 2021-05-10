#include "Game.h"

#include <windows.h>

int WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	GA::Game game;
	return game.run();
}
