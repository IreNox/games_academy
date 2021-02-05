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
		double					m_lastTime		= 0.0;

		float					m_rectX			= 100.0f;
		float					m_rectY			= 100.0f;

		void					update();
		void					render();

		void					drawRect( float x, float y, float w, float h, uint32_t color );
	};
}
