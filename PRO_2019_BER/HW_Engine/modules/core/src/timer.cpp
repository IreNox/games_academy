#include "hw/core/timer.h"

namespace hw
{
	void Timer::create()
	{
		QueryPerformanceFrequency( &m_timeFrequency );
		QueryPerformanceCounter( &m_startTime );
	}

	double Timer::get() const
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter( &currentTime );

		return double( currentTime.QuadPart - m_startTime.QuadPart ) / double( m_timeFrequency.QuadPart );
	}
}