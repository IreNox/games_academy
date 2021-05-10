#include "Game.h"

#include "Collision.h"
#include "RenderData.h"
#include "Transform.h"
#include "Player.h"

#include "CollisionProgram.h"

#include <framework.h>

namespace GA
{
	int Game::run()
	{
		static const ga_graphics_color BackgroundColor = ga_graphics_color_rgb( 0x01u, 0x65u, 0xfcu );

		if( !createSystems() )
		{
			return 1;
		}

		bool running = true;
		double lastTime = 0.0;
		while( running )
		{
			const double gameTime = (double)ga_timer_get( m_pTimer );
			const double deltaTime = gameTime - lastTime;

			ga_input_update( m_pInput );

			if( ga_input_was_mouse_button_pressed( m_pInput, ga_input_mouse_button_middle ) )
			{
				running = false;
			}

			update();

			ga_graphics_begin_frame( m_pGraphics );
			ga_graphics_clear( m_pGraphics, BackgroundColor );
			render();
			ga_graphics_end_frame( m_pGraphics );
		}

		destroySystems();
		return 0;
	}

	bool Game::createSystems()
	{
		m_pTimer = ga_timer_create();
		if( m_pTimer == nullptr )
		{
			return false;
		}

		m_pGraphics = ga_graphics_create( 1280, 720, u8"Pong 🚀" );
		if( m_pGraphics = nullptr )
		{
			destroySystems();
			return false;
		}

		m_pInput = ga_input_create( m_pGraphics );
		if( m_pInput == nullptr )
		{
			destroySystems();
			return false;
		}

		if( !m_entitySystem.create( m_pInput, m_pGraphics ) )
		{
			destroySystems();
			return false;
		}

		m_entitySystem.registerComponentType( TransformComponent::TypeId, TransformComponent::createState );
		m_entitySystem.registerComponentType( CollisionComponent::TypeId, CollisionComponent::createState );
		m_entitySystem.registerComponentType( RenderDataComponent::TypeId, RenderDataComponent::createState );

		CollisionProgram::registerProgram( m_entitySystem );
		PlayerProgram::registerProgram( m_entitySystem );
		BallProgram::registerProgram( m_entitySystem );

		return true;
	}

	void Game::destroySystems()
	{
		m_entitySystem.destroy();

		if( m_pInput != nullptr )
		{
			ga_input_destroy( m_pInput );
			m_pInput = nullptr;
		}

		if( m_pGraphics != nullptr )
		{
			ga_graphics_destroy( m_pGraphics );
			m_pGraphics = nullptr;
		}

		if( m_pTimer != nullptr )
		{
			ga_timer_destroy( m_pTimer );
			m_pTimer = nullptr;
		}
	}

	bool Game::createGame()
	{
		TransformInitData playerTransformInitData;
		playerTransformInitData.x = 50.0f;
		playerTransformInitData.y = 500.0f;

		CollisionInitData playerCollisionInitData;
		playerCollisionInitData.width	= 50.0f;
		playerCollisionInitData.height	= 250.0f;

		const EntityCreateComponentData playerComponents[] =
		{
			{ TransformComponent::TypeId, &playerTransformInitData },
			{ CollisionComponent::TypeId, &playerTransformInitData },
			{ PlayerComponent::TypeId, nullptr },
			{ RenderDataComponent::TypeId, nullptr }
		};

		m_playerId = m_entitySystem.createEntity( playerComponents, ARRAY_COUNT( playerComponents ) );

		return true;
	}

	void Game::destroyGame()
	{

	}

	void Game::update()
	{
	}

	void Game::render()
	{
	}
}
