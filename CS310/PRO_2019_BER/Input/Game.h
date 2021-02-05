#pragma once

#include "Graphics.h"
#include "Input.h"
#include "Timer.h"

#include <stdint.h>

namespace GA
{
	class Game
	{
	public:

		void					run();

	private:

		Graphics				m_graphics;
		Input					m_input;

		Timer					m_timer;

		bool					m_running		= true;

		void					update();
		void					render();

		void					drawRect( float x, float y, float w, float h, uint32_t color );
	};
}
