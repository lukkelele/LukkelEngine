#include <LukkelEngine/Core/Application.h>
#include <LukkelEngine/Core/Window.h>
#include <Platform/Windows/Windows_Window.h>


namespace LukkelEngine {

	Application::Application()
	{
	#ifdef LK_PLATFORM_WINDOWS
		// m_Window = new Windows_Window(WindowProps());
		Window m_Window(WindowProps());
	#endif
	}

	Application::~Application()
	{
		LK_CORE_CRITICAL("Terminating application");
	}


}
