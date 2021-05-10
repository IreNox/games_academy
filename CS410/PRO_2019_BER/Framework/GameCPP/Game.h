#pragma once

#include "EntitySystem.h"

namespace GA
{
	class Game
	{
	public:

		int				run();

	private:

		ga_timer_t*		m_pTimer;
		ga_graphics_t*	m_pGraphics;
		ga_input_t*		m_pInput;

		EntitySystem	m_entitySystem;

		EntityId		m_playerId;
		EntityId		m_enemyId;
		EntityId		m_ballId;

		bool			createSystems();
		void			destroySystems();

		bool			createGame();
		void			destroyGame();

		void			update();
		void			render();
	};
}

