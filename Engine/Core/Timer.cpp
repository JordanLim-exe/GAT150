#include "pch.h"
#include "Timer.h"

namespace nc {
	void nc::Timer::Reset()
	{
		m_tp = clock::now();
	}

	Timer::clock::rep nc::Timer::ElapsedTicks()
	{
		clock::duration duration = (clock::now() - m_tp);

		return duration.count();
	}

	Timer::clock::rep nc::Timer::TicksPerSecond()
	{
		return clock_duration::period::den;
	}

	double nc::Timer::ElapsedSeconds()
	{
		return ElapsedTicks() / static_cast<double>(TicksPerSecond());
	}

	void FrameTimer::Tick() {
		m_dt = ElapsedSeconds();
		m_tp = clock::now();
	}
}

