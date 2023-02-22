#include "LukkelEngine/Core/Window.h"

#ifdef LK_PLATFORM_WINDOWS
	#include <Platform/Windows/Windows_Window.h>
#elif defined(LK_PLATFORM_LINUX)
    #include "Platform/Linux/Linux_Window.h" 
#endif

namespace LukkelEngine {

	s_ptr<Window> Window::create(WindowProps& props)
	{
		#ifdef LK_PLATFORM_WINDOWS
			return std::make_unique<Windows_Window>(props);
		#else
			// return std::make_unique<Linux_Window>(props);
			return std::make_shared<Linux_Window>(props);
		#endif
	}
}
