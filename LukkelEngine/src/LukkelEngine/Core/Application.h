#pragma once

#include <LukkelEngine/Core/Base.h>
#include <LukkelEngine/Core/Window.h>
#include <LukkelEngine/Layer/LayerStack.h>
#include <LukkelEngine/Event/Event.h>
#include <LukkelEngine/Event/ApplicationEvent.h>

#include <LukkelEngine/Test/Test.h>
#include <Platform/Windows/Windows_Window.h>


namespace LukkelEngine {

	struct ApplicationDetails
	{
		std::string name = "LukkelEngine - Dev - Application";
		std::string directory;
	};

	class Application
	{
	private:
		ApplicationDetails details;
		static Application* s_Instance;
		// std::unique_ptr<Window> m_Window; // FIXME: Only Windows Window supported right now
		// std::unique_ptr<Windows_Window> m_Window;
		// Window* m_Window;
		Windows_Window* m_Window;

		test::Test* currentTest = nullptr;
		test::TestMenu* testMenu;

	public:
		Application();
		~Application();
		void tick(uint8_t = 1);
	
	};
}