#include "Game.h"

#include <d3d11.h>

namespace GA
{
	void Game::run()
	{
		if( !m_graphics.initialize() )
		{
			return;
		}

		while(m_graphics.isOpen() )
		{
			update();
			render();
		}

		m_graphics.shutdown();
	}

	void Game::update()
	{
		m_graphics.update();
	}

	void Game::render()
	{
		const float backgroundColor[] = { 0.0f, 0.5f, 1.0f, 1.0f };
		ID3D11DeviceContext* pContext = m_graphics.beginFrame( backgroundColor );

		const GameVertex vertices[] =
		{
			{ {  100.0f,  0.5f, 0.0f }, { 1.0f, 0.0f, 0.0f, 1.0f } },
			{ {  0.5f, -0.5f, 0.0f }, { 0.0f, 1.0f, 0.0f, 1.0f } },
			{ { -0.5f, -0.5f, 0.0f }, { 0.0f, 0.0f, 1.0f, 1.0f } }
		};

		m_graphics.draw( vertices, ARRAY_COUNT( vertices ) );

		m_graphics.endFrame();
	}
}
