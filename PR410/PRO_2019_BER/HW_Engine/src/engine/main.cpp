#include "hw/core/string.h"
#include "hw/framework/framework.h"

#include "../test/tests.h"

#include <Windows.h>

namespace hw
{
	int run()
	{
#if 1
		testSpmcQueue();
		return 0;
#endif

		Framework framework;
		return framework.run();
	}
}

int WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	return hw::run();
}
