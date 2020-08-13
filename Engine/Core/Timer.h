#pragma once
#include <chrono>

namespace nc {
	class Timer {
	public:
		using clock = std::chrono::high_resolution_clock;
		using clock_duration = std::chrono::duration<clock::rep, std::milli>;
	public:
		Timer() : m_tp(clock::now()) {}

		void Reset();

		clock::rep ElapsedTicks();
		clock::rep TicksPerSecond();

		double ElapsedSeconds();

	protected:
		clock::time_point m_tp;
	};

	class FrameTimer : public Timer {
	public:
		void Tick();
		float DeltaTime() {
			return 0.016f;
		}//m_dt; }

	protected:
		float m_dt{ 0 };
	};
}