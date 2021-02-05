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

		if( !m_input.create( m_graphics ) )
		{
			m_graphics.shutdown();
			return;
		}

		while( m_graphics.isOpen() && m_running )
		{
			update();
			render();
		}

		m_input.destroy();
		m_graphics.shutdown();
	}

	void Game::update()
	{
		m_graphics.update();
		m_input.update();

		if (m_input.wasKeyboardKeyPressed(InputKeyboardKey::Escape))
		{
			m_running = false;
		}
	}

	void Game::render()
	{
		const float backgroundColor[] = { 0.0f, 0.5f, 1.0f, 1.0f };
		ID3D11DeviceContext* pContext = m_graphics.beginFrame( backgroundColor );

		drawRect(100.0f, 100.0f, 100.0f, 100.0f, 0xffae00ff);
		drawRect(300.0f, 100.0f, 100.0f, 100.0f, 0x1d7328ff);
		drawRect(500.0f, 100.0f, 100.0f, 100.0f, 0xff0000ff);
		drawRect(700.0f, 100.0f, 100.0f, 100.0f, 0x00ff00ff);

		m_graphics.endFrame();
	}

	void Game::drawRect( float x, float y, float w, float h, uint32_t color )
	{
		const float cr = float( (color >> 24u) & 0xff ) / 255.0f;	// ffae00ff >> 24 = 000000ff & 0xff = 000000ff
		const float cg = float( (color >> 16u) & 0xff ) / 255.0f;	// ffae00ff >> 16 = 0000ffae & 0xff = 000000ae
		const float cb = float( (color >>  8u) & 0xff ) / 255.0f;	// ffae00ff >>  8 = 00ffae00 & 0xff = 00000000
		const float ca = float( (color >>  0u) & 0xff ) / 255.0f;	// ffae00ff >>  0 = ffae00ff & 0xff = 000000ff

		const float r = x + w;
		const float b = y + h;
		const GameVertex vertices[] =
		{
			// Triangle 1
			// 0--1
			//  \ |
			//   \|
			//    2
			{ { x,	y,	0.0f }, { cr, cg, cb, ca } },
			{ { r,	y,	0.0f }, { cr, cg, cb, ca } },
			{ { r,	b,	0.0f }, { cr, cg, cb, ca } },

			// Triangle 2
			// 0
			// |\
			// | \
			// 2--1
			{ { x,	y,	0.0f }, { cr, cg, cb, ca } },
			{ { r,	b,	0.0f }, { cr, cg, cb, ca } },
			{ { x,	b,	0.0f }, { cr, cg, cb, ca } }
		};

		m_graphics.draw( vertices, ARRAY_COUNT( vertices ) );
	}
}
