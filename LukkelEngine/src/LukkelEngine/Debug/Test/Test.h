#pragma once
#include "LukkelEngine/Core/LKErrorHandler.h"
#include "imgui/imgui.h"

namespace LukkelEngine {

	namespace test {

		class Test
		{
		public:
			Test() {}
			virtual ~Test() {}

			virtual void OnUpdate(float deltaTime) {}
			virtual void onRender() {}
			virtual void OnImGuiRender() {}
		};


		class TestMenu : public Test
		{
		public:
			TestMenu(Test*& currentTestPointer);

			virtual void OnImGuiRender() override;

			template<typename T>
			void registerTest(const std::string& name)
			{
				m_tests.push_back(std::make_pair(name, []() { return new T; }));
			}

		private:
			Test*& m_currentTest;
			/* Vector [ String name, Test pointer ] -> instantiate tests on the fly */
			std::vector<std::pair<std::string, std::function<Test*()>>> m_tests;
			// Test*() is a type conversion -> user defined conversion
		};
	}
}
