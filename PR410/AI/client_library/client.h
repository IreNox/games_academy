#pragma once

#include "client_library.h"
#include "connection.h"

#include "framework/font.h"
#include "framework/graphics.hpp"
#include "framework/input.hpp"
#include "framework/timer.hpp"

namespace GamesAcademy
{
	class Client
	{
	public:

		int			run( const char* pUsername, DoActionCallback pCallback, void* pUserData );

	private:

		enum class PlayerInputState
		{
			Walk,
			Shoot
		};

		Graphics			m_graphics;
		Font				m_font;
		Input				m_input;
		Timer				m_timer;

		Connection			m_connection;

		DoActionCallback	m_pCallback			= nullptr;
		void*				m_pUserData			= nullptr;
		uint32				m_lastRound			= 0u;
		uint8				m_lastAction		= 0u;

		float				m_minSize			= 0.0f;
		float				m_border			= 0.0f;
		float				m_spacing			= 0.0f;
		float				m_cellSize			= 0.0f;
		float				m_halfSize			= 0.0f;
		float				m_playerBegin		= 0.0f;
		float				m_playerEnd			= 0.0f;

		bool				create();
		void				destroy();

		void				update();
		void				render();
		void				renderShoot( const MessageShootState& shoot );

		float				getCellPosition( uint8 pos ) const;
	};
}
