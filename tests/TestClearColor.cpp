#include <TestClearColor.h>

namespace test {

	ClearColor::ClearColor()
		: m_clearColor { 0.2f, 0.3f, 0.8f, 1.0f }
	{

	}

	ClearColor::~ClearColor()
	{

	}

	void ClearColor::onUpdate(float deltaTime)
	{

	}

	void ClearColor::onRender()
	{
		GLCall(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}

	void ClearColor::onImGuiRender()
	{
		ImGui::ColorEdit4("Clear Color", m_clearColor);
	}

}