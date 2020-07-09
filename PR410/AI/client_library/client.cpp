#include "client.h"

#define _USE_MATH_DEFINES
#include <math.h>
#include <minmax.h>

#include <stdio.h>

namespace GamesAcademy
{
	template <typename T> T sgn( T val )
	{
		return T((T( 0 ) < val) - (val < T( 0 )));
	}

	int Client::run( const char* pUsername, DoActionCallback pCallback, void* pUserData )
	{
		m_pCallback = pCallback;
		m_pUserData = pUserData;

		if( !create() )
		{
			return 1;
		}

		m_connection.login( pUsername );

		while( m_graphics.isWindowOpen() )
		{
			update();
			render();
		}

		destroy();
		return 0;
	}

	bool Client::create()
	{
		if( !m_graphics.create( 1280u, 720u, "Client" ) )
		{
			return false;
		}

		if( !m_font.create( m_graphics, "C:\\Windows\\Fonts\\arial.ttf", 64 ) )
		{
			return false;
		}

		if( !m_input.create( m_graphics ) )
		{
			return false;
		}

		if( !m_connection.create() )
		{
			return false;
		}

		m_timer.create();

		return true;
	}

	void Client::destroy()
	{
		m_connection.destroy();
		m_input.destroy();
		m_font.destroy();
		m_graphics.destroy();

		m_pCallback = nullptr;
	}

	void Client::update()
	{
		m_input.update();
		m_connection.update( m_timer.get() );

		if( m_connection.getState() != ConnectionState::Playing )
		{
			return;
		}

		const MessageGameState& gameState = m_connection.getGameState();
		const MessagePlayerState* pPlayer = nullptr;
		for( size_t i = 0u; i < gameState.playerCount; ++i )
		{
			if( gameState.players[ i ].playerId != m_connection.getPlayerId() )
			{
				continue;
			}

			pPlayer = &gameState.players[ i ];
		}

		if( pPlayer == nullptr
			 )
		{
			return;
		}

		if( gameState.round != m_lastRound )
		{
			m_lastAction	= m_pCallback( (const GameState*)&gameState, m_pUserData );
			m_lastRound		= gameState.round;
		}

		const MessagePlayerActionType actionType = (MessagePlayerActionType)m_lastAction;
		m_connection.action( actionType );
	}

	void Client::render()
	{
		m_graphics.beginFrame();
		m_graphics.clear( 0xff000000 );

		if( m_connection.getState() != ConnectionState::Playing )
		{
			m_graphics.drawText( 50.0f, 50.0f, 24.0f, m_font, "Connecting...", 0xffffffffu );
			m_graphics.endFrame();
			return;
		}

		m_minSize		= min( m_graphics.getBackBufferWidth(), m_graphics.getBackBufferHeight() );
		m_border		= m_minSize * 0.05f;
		m_spacing		= 2.0f;
		m_cellSize		= (m_minSize - (2.0f * m_border) - (16.0f * m_spacing)) / 16.0f;
		m_halfSize		= m_cellSize * 0.5f;
		m_playerBegin	= m_cellSize * 0.1f;
		m_playerEnd		= m_cellSize * 0.9f;

		for( uint8 y = 0u; y < 16u; ++y )
		{
			for( uint8 x = 0u; x < 16u; ++x )
			{
				const float cellX = getCellPosition( x );
				const float cellY = getCellPosition( y );

				m_graphics.drawRect( cellX, cellY, m_cellSize, m_cellSize, 0xffdd6622u );
			}
		}

		const MessageGameState& gameState = m_connection.getGameState();
		const MessagePlayerState* pPlayer = nullptr;
		for( uint8 playerIndex = 0u; playerIndex < gameState.playerCount; ++playerIndex )
		{
			const MessagePlayerState& player = gameState.players[ playerIndex ];

			if( player.playerId == m_connection.getPlayerId() )
			{
				pPlayer = &player;
			}

			const float playerX = getCellPosition( player.positionX );
			const float playerY = getCellPosition( player.positionY );

			m_graphics.drawTriangle(
				playerX + m_halfSize,		playerY + m_playerBegin,
				playerX + m_playerEnd,		playerY + m_playerEnd,
				playerX + m_playerBegin,	playerY + m_playerEnd,
				0xff77cc44u
			);
		}

		for( uint8 shootIndex = 0u; shootIndex < gameState.shootCount; ++shootIndex )
		{
			renderShoot( gameState.shoots[ shootIndex ] );
		}

		m_graphics.endFrame();
	}

	void Client::renderShoot( const MessageShootState& shoot )
	{
		const float directionX		= -sgn( float( shoot.startPositionX ) - shoot.endPositionX );
		const float directionY		= -sgn( float( shoot.startPositionY ) - shoot.endPositionY );
		const float startX			= getCellPosition( shoot.startPositionX ) + (directionX * m_halfSize) + m_halfSize;
		const float startY			= getCellPosition( shoot.startPositionY ) + (directionY * m_halfSize) + m_halfSize;
		const float endX			= getCellPosition( shoot.endPositionX ) + m_halfSize;
		const float endY			= getCellPosition( shoot.endPositionY ) + m_halfSize;
		const float offsetX			= directionX * m_halfSize;
		const float offsetY			= directionY * m_halfSize;

		if( directionX != directionY )
		{
			m_graphics.drawTriangle(
				startX, startY + offsetY,
				endX, endY,
				startX + offsetX, startY,
				0xff1144ddu
			);
		}
		else
		{
			m_graphics.drawTriangle(
				startX, startY + offsetY,
				startX + offsetX, startY,
				endX, endY,
				0xff1144ddu
			);
		}
	}

	float Client::getCellPosition( uint8 pos ) const
	{
		return m_border + (pos * (m_cellSize + m_spacing)) + m_spacing;
	}
}
