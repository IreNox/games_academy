#pragma once

#include <stdint.h>

#ifdef GA_EXPORT
#	define GA_DLL __declspec(dllexport)
#else
#	define GA_DLL __declspec(dllimport)
#endif

extern "C"
{
	struct PlayerState
	{
		uint8_t			playerId;
		uint8_t			positionX;
		uint8_t			positionY;
	};

	struct ShootState
	{
		uint8_t			playerId;
		uint8_t			startPositionX;
		uint8_t			startPositionY;
		uint8_t			endPositionX;
		uint8_t			endPositionY;
	};

	struct GameState
	{
		uint32_t		round;
		PlayerState		players[ 8u ];
		uint8_t			playerCount;
		ShootState		shoots[ 8u ];
		uint8_t			shootCount;
	};

	enum PlayerActionType
	{
		PlayerActionType_Invalid,
		PlayerActionType_MoveUp,
		PlayerActionType_MoveDown,
		PlayerActionType_MoveLeft,
		PlayerActionType_MoveRight,
		PlayerActionType_ShootUpLeft,
		PlayerActionType_ShootUpRight,
		PlayerActionType_ShootDownLeft,
		PlayerActionType_ShootDownRight
	};

	typedef uint8_t(*DoActionCallback)(const GameState* pGameState, uint8_t myPlayerId, void* pUserData);

	void GA_DLL runClient( const char* pUsername, DoActionCallback pCallback, void* pUserData );
}