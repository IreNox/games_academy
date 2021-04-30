#include "game_application.h"

#include "hw/framework/framework.h"
#include "hw/graphics/graphics_system.h"
#include "hw/resource/resource_system.h"

namespace hw
{
	bool GameApplication::create( Framework* pFramework )
	{
		m_pFramework = pFramework;

		m_pLoadContext = pFramework->getResourceSystem()->beginLoadResource( "checker_rgb" );

		return true;
	}

	void GameApplication::destroy()
	{
		if( m_pResource != nullptr )
		{
			m_pFramework->getResourceSystem()->unloadResource( m_pResource );
			m_pResource = nullptr;
		}
	}

	void GameApplication::update()
	{
		if( m_pLoadContext != nullptr )
		{
			const ResourceLoadResult result = m_pFramework->getResourceSystem()->finishLoadResource( m_pLoadContext );
			if( result.isDone )
			{
				m_pResource		= result.pResource;
				m_pLoadContext	= nullptr;
			}
		}
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