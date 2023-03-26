#include "LKpch.h"
#include "LukkelEngine/Debug/Test/TestClearColor.h"

namespace LukkelEngine {

	namespace test {

		TestClearColor::TestClearColor()
			: m_clearColor { 0.2f, 0.3f, 0.8f, 1.0f }
		{
		}

		TestClearColor::~TestClearColor()
		{
		}

		void TestClearColor::OnUpdate(float deltaTime)
		{
		}

		void TestClearColor::onRender()
		{
			GLCall(glClearColor(m_clearColor[0], m_clearColor[1], m_clearColor[2], m_clearColor[3]));
			GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
		}

		void TestClearColor::OnImGuiRender()
		{
			ImGui::ColorEdit4("Clear Color", m_clearColor);
		}

	}
}