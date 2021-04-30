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
		if( m_pTexture != nullptr )
		{
			m_pFramework->getResourceSystem()->unloadResource( m_pTexture );
			m_pTexture = nullptr;
		}
	}

	void GameApplication::update()
	{
		if( m_pLoadContext != nullptr )
		{
			const ResourceLoadResult result = m_pFramework->getResourceSystem()->finishLoadResource( m_pLoadContext );
			if( result.isDone )
			{
				m_pTexture		= (TextureResource*)result.pResource;
				m_pLoadContext	= nullptr;
			}
		}
	}

	void GameApplication::render()
	{
		if( m_pTexture == nullptr )
		{
			return;
		}

		m_pFramework->getGraphicsSystem()->drawRect( 50.0f, 50.0f, 500.0f, 500.0f, 0xffffffffu, m_pTexture );
	}

	Application& getApplication()
	{
		static GameApplication app;
		return app;
	}
}