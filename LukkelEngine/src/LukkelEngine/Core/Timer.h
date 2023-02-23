#pragma once

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
		* @brief Reset the timer
		*/
		void Timer::reset()
		{
			m_Start = std::chrono::high_resolution_clock::now();
		}

	   /**
		* @brief Get elapsed time since m_Start in nanoseconds
		* @returns time elapsed in nanoseconds
		*/
		float Timer::elapsed()
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>
				(std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f * 0.001f * 0.001f;
		}

	   /**
		* @brief Get elapsed time since m_Start in milliseconds
		* @returns time elapsed in milliseconds
		*/
		float Timer::elapsedMs()
		{
			return elapsed() * 1000.0f;
		}

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
	};
}
