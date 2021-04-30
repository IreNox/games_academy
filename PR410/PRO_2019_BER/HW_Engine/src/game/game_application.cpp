#include "game_application.h"

namespace hw
{
	bool GameApplication::create( Framework* pFramework )
	{
		return true;
	}

	void GameApplication::destroy()
	{
	}

	void GameApplication::update()
	{
	}

	void GameApplication::render()
	{
	}

	Application& getApplication()
	{
		static GameApplication app;
		return app;
	}
}