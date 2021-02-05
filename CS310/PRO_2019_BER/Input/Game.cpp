#include "Game.h"

#include <d3d11.h>

namespace GA
{
	static const float s_rectWidth	= 100.0f;
	static const float s_rectHeight	= 100.0f;

	template< class T >
	T clamp( T value, T min, T max )
	{
		return value < min ? min : (value > max ? max : value);
	}

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

		m_timer.create();

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

		if( m_input.wasKeyboardKeyPressed( InputKeyboardKey::Escape ) ||
			m_input.wasGamepadButtonPressed( InputGamepadButton::Start ) )
		{
			m_running = false;
		}

		const double gameTime = m_timer.get();
		const double deltaTime = gameTime - m_lastTime;
		m_lastTime = gameTime;

		float moveX = 0.0f;
		float moveY = 0.0f;
		if (m_input.isKeyboardKeyDown(InputKeyboardKey::A) ||
			m_input.isKeyboardKeyDown(InputKeyboardKey::Left))
		{
			moveX -= 1.0f;
		}

		if (m_input.isKeyboardKeyDown(InputKeyboardKey::D) ||
			m_input.isKeyboardKeyDown(InputKeyboardKey::Right))
		{
			moveX += 1.0f;
		}

		if (m_input.isKeyboardKeyDown(InputKeyboardKey::W) ||
			m_input.isKeyboardKeyDown(InputKeyboardKey::Up))
		{
			moveY -= 1.0f;
		}

		if (m_input.isKeyboardKeyDown(InputKeyboardKey::S) ||
			m_input.isKeyboardKeyDown(InputKeyboardKey::Down))
		{
			moveY += 1.0f;
		}

		moveX += m_input.getGamepadAxis( InputGamepadAxis::LeftX );
		moveY -= m_input.getGamepadAxis( InputGamepadAxis::LeftY );

		moveY += m_input.getGamepadAxis( InputGamepadAxis::TriggerLeft );
		moveY -= m_input.getGamepadAxis( InputGamepadAxis::TriggerRight );

		moveX = clamp( moveX, -1.0f, 1.0f );
		moveY = clamp( moveY, -1.0f, 1.0f );

		const float speed = 300.0f;
		m_rectX += float( moveX * speed * deltaTime );
		m_rectY += float( moveY * speed * deltaTime );

		if (m_input.isMouseButtonDown(InputMouseButton::Left))
		{
			m_rectX = m_input.getMousePositionX() - (s_rectWidth / 2.0f);
			m_rectY = m_input.getMousePositionY() - (s_rectHeight / 2.0f);
		}
	}

	void Game::render()
	{
		const float backgroundColor[] = { 0.0f, 0.5f, 1.0f, 1.0f };
		ID3D11DeviceContext* pContext = m_graphics.beginFrame( backgroundColor );

		drawRect( m_rectX, m_rectY, s_rectWidth, s_rectHeight, 0xffae00ff );

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
