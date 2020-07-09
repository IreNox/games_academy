#include "../client_library/client_library.h"

#include <math.h>
#include <stdlib.h>
#include <windows.h>

const PlayerState* findPlayer( const GameState* pGameState, uint8_t playerId )
{
	for( size_t i = 0u; i < pGameState->playerCount; ++i )
	{
		if( pGameState->players[ i ].playerId == playerId )
		{
			return &pGameState->players[ i ];
		}
	}

	return nullptr;
}

const PlayerState* findNearestEnemy( const GameState* pGameState, const PlayerState* pMyPlayer )
{
	const float myX = float( pMyPlayer->positionX );
	const float myY = float( pMyPlayer->positionY );

	float minDistance = 1000.0f;
	const PlayerState* pNearestEnemy = nullptr;
	for( size_t i = 0u; i < pGameState->playerCount; ++i )
	{
		const PlayerState& enemy = pGameState->players[ i ];
		if( enemy.playerId == pMyPlayer->playerId )
		{
			continue;
		}

		const float distanceX = myX - enemy.positionX;
		const float distanceY = myY - enemy.positionY;
		const float distance = sqrtf(distanceX * distanceX + distanceY * distanceY);
		if( distance < minDistance )
		{
			minDistance = distance;
			pNearestEnemy = &enemy;
		}

		return pNearestEnemy;
	}

	return nullptr;
}

uint8_t doAction( const GameState* pGameState, uint8_t myPlayerId, void* pUserData )
{
	const PlayerState* pMyPlayer = findPlayer( pGameState, myPlayerId );
	if( pMyPlayer == nullptr )
	{
		return (rand() % PlayerActionType_MoveRight) + 1;
	}

	const PlayerState* pEnemy = findNearestEnemy( pGameState, pMyPlayer );
	if( pEnemy == nullptr )
	{
		return (rand() % PlayerActionType_MoveRight) + 1;
	}

	const float myX				= float( pMyPlayer->positionX );
	const float myY				= float( pMyPlayer->positionY );
	const float enemyX			= float( pEnemy->positionX );
	const float enemyY			= float( pEnemy->positionY );
	const float distanceX		= enemyX - myX;
	const float distanceY		= enemyY - myY;
	const float absDistanceX	= fabsf( distanceX );
	const float absDistanceY	= fabsf( distanceY );

	if( distanceX != 0.0f && distanceY != 0.0f && absDistanceX == absDistanceY )
	{
		if( distanceX > 0.0f && distanceY > 0.0f )
		{
			return PlayerActionType_ShootDownRight;
		}
		else if( distanceX < 0.0f && distanceY > 0.0f )
		{
			return PlayerActionType_ShootDownLeft;
		}
		else if( distanceX < 0.0f && distanceY < 0.0f )
		{
			return PlayerActionType_ShootUpLeft;
		}
		else if( distanceX > 0.0f && distanceY < 0.0f )
		{
			return PlayerActionType_ShootUpRight;
		}
	}
	else
	{
		const float wayLeft		= (enemyX - absDistanceY) - myX;
		const float wayRight	= (enemyX + absDistanceY) - myX;
		const float wayUp		= (enemyY - absDistanceX) - myY;
		const float wayDown		= (enemyY + absDistanceX) - myY;
		//const bool canMoveLeft	= myX + wayLeft >= 0.0f && !(distanceY >= -1.0f && distanceX == 0.0f) && distanceY != 0.0f;
		//const bool canMoveRight	= myX - wayRight <= 15.0f && !(distanceY >= 1.0f && distanceX == 0.0f) && distanceY != 0.0f;
		//const bool canMoveUp	= myY + wayUp >= 0.0f && !(distanceY >= -1.0f && distanceX == 0.0f) && distanceX != 0.0f;
		//const bool canMoveDown	= myY - wayDown <= 15.0f && !(distanceY >= 1.0f && distanceX == 0.0f) && distanceX != 0.0f;

		const float wayX		= fabsf( wayLeft ) < fabsf( wayRight ) /*&& canMoveLeft*/ ? wayLeft : wayRight;
		const float wayY		= fabsf( wayUp ) < fabsf( wayDown ) /*&& canMoveUp*/ ? wayUp : wayDown;

		const bool canMoveLeft	= myX + wayX >= 0.0f && !(distanceY >= -1.0f && distanceX == 0.0f) && distanceY != 0.0f;
		const bool canMoveRight	= myX + wayX <= 15.0f && !(distanceY >= 1.0f && distanceX == 0.0f) && distanceY != 0.0f;
		const bool canMoveUp	= myY + wayY >= 0.0f && !(distanceY >= -1.0f && distanceX == 0.0f) && distanceX != 0.0f;
		const bool canMoveDown	= myY + wayY <= 15.0f && !(distanceY >= 1.0f && distanceX == 0.0f) && distanceX != 0.0f;

		const bool shouldGoX	= fabsf( wayX ) <= fabsf( wayY ) && (canMoveLeft || canMoveRight);
		const bool shouldGoY	= fabsf( wayX ) >= fabsf( wayY ) && (canMoveUp || canMoveDown);

		if( shouldGoX && !shouldGoY )
		{
			if( wayX < 0.0f && canMoveLeft )
			{
				return PlayerActionType_MoveLeft;
			}
			else if( canMoveRight )
			{
				return PlayerActionType_MoveRight;
			}
		}
		else
		{
			if( wayY < 0.0f && canMoveUp )
			{
				return PlayerActionType_MoveUp;
			}
			else if( canMoveDown )
			{
				return PlayerActionType_MoveDown;
			}
		}

		return (rand() % PlayerActionType_MoveRight) + 1;

		//const float wayX		= (enemyX + absDistanceY) - myX;
		//const float wayY		= (enemyY + absDistanceX) - myY;
		//const bool canMoveLeft	= myX + wayX >= 0.0f && !(distanceY >= -1.0f && distanceX == 0.0f);
		//const bool canMoveRight	= myX + wayX <= 15.0f && !(distanceY >= 1.0f && distanceX == 0.0f);
		//const bool canMoveUp	= myY + wayY >= 0.0f && !(distanceY >= -1.0f && distanceX == 0.0f);
		//const bool canMoveDown	= myY + wayY <= 15.0f && !(distanceY >= 1.0f && distanceX == 0.0f);
		//const bool shouldGoX	= fabsf( wayX ) <= fabsf( wayY ) && (canMoveLeft || canMoveRight);
		//const bool shouldGoY	= fabsf( wayX ) >= fabsf( wayY ) && (canMoveUp || canMoveDown);

		//if( shouldGoX && !shouldGoY )
		//{
		//	if( wayX < 0.0f && canMoveLeft )
		//	{
		//		return PlayerActionType_MoveLeft;
		//	}
		//	else if( canMoveRight )
		//	{
		//		return PlayerActionType_MoveRight;
		//	}
		//}
		//else
		//{
		//	if( wayY < 0.0f && canMoveUp )
		//	{
		//		return PlayerActionType_MoveUp;
		//	}
		//	else if( canMoveDown )
		//	{
		//		return PlayerActionType_MoveDown;
		//	}
		//}

		//return (pGameState->round % PlayerActionType_MoveRight) + 1;

	}

	return PlayerActionType_Invalid;
}

int __stdcall WinMain( _In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd )
{
	runClient( "Tim", doAction, nullptr );
	return 0;
}
