#pragma once

#include <chrono>

namespace LukkelEngine {

	class Timer
	{
	public:
		Timer()
		{
			Reset();
		}

	   /**
		* @brief Reset the timer
		*/
		void Timer::Reset()
		{
			m_Start = std::chrono::high_resolution_clock::now();
		}

	   /**
		* @brief Get elapsed time since m_Start in nanoseconds
		* @returns time elapsed in nanoseconds
		*/
		float Timer::Elapsed()
		{
			return std::chrono::duration_cast<std::chrono::nanoseconds>
				(std::chrono::high_resolution_clock::now() - m_Start).count() * 0.001f * 0.001f * 0.001f;
		}

	   /**
		* @brief Get elapsed time since m_Start in milliseconds
		* @returns time elapsed in milliseconds
		*/
		float Timer::ElapsedMs()
		{
			return Elapsed() * 1000.0f;
		}

		float Timer::getDeltaTime()
		{
			float now = ElapsedMs();
			float deltaTime = now - m_LastTime;
			m_LastTime = now;
			return deltaTime;
		}

	private:
		std::chrono::time_point<std::chrono::high_resolution_clock> m_Start;
		float m_LastTime = 0.0f;
	};
}
