#pragma once

#include "Graphics.h"

namespace GA
{
	class Game
	{
	public:

		void					run();

	private:

		Graphics				m_graphics;

		void					update();
		void					render();
	};
}
