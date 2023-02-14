#ifndef _LKENGINE_TIMER_H
#define _LKENGINE_TIMER_H

#include <chrono>

namespace LukkelEngine {

	class Timer
	{
	public:
		Timer()
		{
			reset();
		}

	   /**
		*  Reset timer
		*/
		void Timer::reset()
		{
			m_Start = std::chrono::high_resolution_clock::now();
		}

	   /**
		*  Get elapsed time since m_Start
		*/
		float Timer::elapsed()
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>
				(std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f * 0.001f * 0.001f;
		}

	   /**
		*  Get elapsed time since m_Start in milliseconds
		*/
		float Timer::elapsedMs()
		{
			return elapsed() * 1000.0f;
		}

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	};

}

#endif /* _LKENGINE_TIMER_H */