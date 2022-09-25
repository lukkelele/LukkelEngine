#pragma once

#include <GLErrorHandler.h>
#include <imgui/imgui.h>
#include <functional>
#include <vector>

/* 
	Test interface
*/

namespace test {

	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void onUpdate(float deltaTime) {}
		virtual void onRender() {}
		virtual void onImGuiRender() {}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& currentTestPointer);

		virtual void onImGuiRender() override;

		template<typename T>
		void registerTest(const std::string& name)
		{
			std::cout << "Registering test " << name << std::endl;

			m_tests.push_back(std::make_pair(name, []() { return new T; }));
		}

	private:
		Test*& m_currentTest;
		/* Vector [ String name, Test pointer ] -> instantiate tests on the fly */
		std::vector< std::pair< std::string, std::function<Test* () >>> m_tests;
	};

}
