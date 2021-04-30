#include "hw/framework/framework.h"

#include <Windows.h>

int WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	hw::Framework framework;
	return framework.run();
}
