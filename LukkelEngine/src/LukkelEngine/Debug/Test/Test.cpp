#include "LKpch.h"
#include "LukkelEngine/Debug/Test/Test.h"

namespace LukkelEngine {
	namespace test {

		TestMenu::TestMenu(Test*& currentTestPointer)
			: m_currentTest(currentTestPointer)
		{

		}

		void TestMenu::OnImGuiRender()
		{
			for (auto& test : m_tests)
			{
				if (ImGui::Button(test.first.c_str())) {
					m_currentTest = test.second();
				}
			}
		}
	}
}
