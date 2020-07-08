#pragma once

#include "message_types.h"

#include <WinSock2.h>
#include <string>

namespace GamesAcademy
{
	enum class ConnectionState
	{
		Invalid,
		Connecting,
		LoggedIn,
		Playing,
		Failed
	};

	class Connection
	{
	public:

		bool					create();
		void					destroy();

		void					update( double gameTime );

		ConnectionState			getState() const { return m_state; }
		uint8					getPlayerId() const { return m_playerId; }
		MessageGameState		getGameState() const { return m_gameState; }

		void					login( const char* pUsername );
		void					action( MessagePlayerActionType action );

	private:

		SOCKET					m_socket			= INVALID_SOCKET;
		sockaddr_in				m_serverAddress;

		ConnectionState			m_state				= ConnectionState::Invalid;
		double					m_lastReceiveTime	= 0.0;
		double					m_lastPingTime		= 0.0;

		std::string				m_username;
		uint8					m_playerId			= 0xffu;
		MessageGameState		m_gameState;

		void					handleLoginResponse( const void* pMessage, size_t messageSize );
		void					handleGameState( const void* pMessage, size_t messageSize );

		void					sendMessage( MessageType type, const void* pMessage, size_t dataSize );
	};
}
