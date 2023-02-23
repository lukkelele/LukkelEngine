#pragma once
/*
	Time is a class to make different refresh rates move the
	rendered objects at the same speed.
*/
namespace LukkelEngine {

	class Timestep
	{
	public:
		Timestep(float time = 0.0f)
			: m_Time(time) 
		{
		}

		operator float() const { return m_Time; }
		float getSeconds() const { return m_Time; }
		float getMilliSeconds() const { return m_Time * 1000.0f; }

	private:
		float m_Time;
	};
}
