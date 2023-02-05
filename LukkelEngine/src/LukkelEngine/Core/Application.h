#pragma once

#include <LukkelEngine/Core/Base.h>
#include <LukkelEngine/Core/Window.h>
#include <LukkelEngine/Core/LayerStack.h>
#include <LukkelEngine/Event/Event.h>
#include <LukkelEngine/Event/ApplicationEvent.h>

int main(int argc, char** argv);

namespace LukkelEngine {

	struct ApplicationDetails
	{
		std::string name = "LukkelEngine - Dev - Application";
	};

	class Application
	{
	private:
		static Application* s_Instance;
		friend int ::main(int argc, char** argv);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
	
	public:
		Application(const ApplicationDetails& details);
		virtual ~Application();

		Window& getWindow() { return *m_Window; }
		static Application& get() { return *s_Instance;  }

		void pushLayer(Layer* layer);
		void popLayer(Layer* layer);
		void onEvent(Event& e);


	};
}