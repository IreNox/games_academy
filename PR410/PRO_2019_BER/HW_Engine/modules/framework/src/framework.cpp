#include "hw/framework/framework.h"

#include "hw/framework/application.h"
#include "hw/graphics/graphics_system.h"
#include "hw/input/input_system.h"
#include "hw/resource/resource_system.h"
#include "hw/sound/sound_system.h"

namespace hw
{
	int Framework::run()
	{
		m_pApplication = &getApplication();

		if ( !create() )
		{
			return 1;
		}

		const float backgroundColor[] = { 0.0f, 0.0f, 0.0f, 0.0f };
		while( m_pGraphicsSystem->isOpen() )
		{
			m_pGraphicsSystem->update();
			m_pInputSystem->update();
			m_pResourceSystem->update();
			m_pSoundSystem->update();

			m_pApplication->update();

			m_pGraphicsSystem->beginFrame( backgroundColor );
			m_pApplication->render();
			m_pGraphicsSystem->endFrame();
		}

		destroy();

		return 0;
	}

	bool Framework::create()
	{
		m_pGraphicsSystem = new GraphicsSystem();
		if( !m_pGraphicsSystem->create() )
		{
			destroy();
			return false;
		}

		m_pInputSystem = new InputSystem();
		if( !m_pInputSystem->create( *m_pGraphicsSystem ) )
		{
			destroy();
			return false;
		}

		m_pResourceSystem = new ResourceSystem();
		if( !m_pResourceSystem->create( "data" ) )
		{
			destroy();
			return false;
		}

		m_pSoundSystem = new SoundSystem();
		if( !m_pSoundSystem->create() )
		{
			destroy();
			return false;
		}

		return m_pApplication->create( this );
	}

	void Framework::destroy()
	{
		m_pApplication->destroy();

		if( m_pSoundSystem != nullptr )
		{
			m_pSoundSystem->destroy();
			delete m_pSoundSystem;
		}

		if( m_pResourceSystem != nullptr )
		{
			m_pResourceSystem->destroy();
			delete m_pResourceSystem;
		}

		if( m_pInputSystem != nullptr )
		{
			m_pInputSystem->destroy();
			delete m_pInputSystem;
		}

		if( m_pGraphicsSystem != nullptr )
		{
			m_pGraphicsSystem->destroy();
			delete m_pGraphicsSystem;
		}
	}
}