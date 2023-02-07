#ifdef LK_USE_PRECOMPILED_HEADERS
	#include <LKpch.h>
#endif
#include <LukkelEngine/Core/Window.h>
#ifdef LK_PLATFORM_WINDOWS
	#include <Platform/Windows/Windows_Window.h>
#endif

namespace LukkelEngine {

	/* OVERLOAD ERROR!
	std::unique_ptr<Window> Window::create(WindowProps& props)
	{
		#ifdef LK_PLATFORM_WINDOWS
			return std::make_unique<Windows_Window>(new Windows_Window(props));
		#else
			LK_CORE_ASSERT(false, "Platform not implemented yet");
			return nullptr;
		#endif
	}
	*/
}