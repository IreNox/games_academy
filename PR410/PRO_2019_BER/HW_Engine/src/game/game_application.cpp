#include "game_application.h"

#include "hw/framework/framework.h"
#include "hw/graphics/graphics_system.h"

namespace hw
{
	bool GameApplication::create( Framework* pFramework )
	{
		m_pFramework = pFramework;

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
		m_pFramework->getGraphicsSystem()->drawRect( 50.0f, 50.0f, 50.0f, 50.0f, 0xffffffffu );
	}

	Application& getApplication()
	{
		static GameApplication app;
		return app;
	}
}