#pragma once
/* 
	LukkelEngine core file.

	> GLFW
		The GLCall macro does not function on some OpenGL functions.
		Debugging can be a pain when the macro is seen as trivial but it can be prone to errors.
		Specific ones to watch out for:
			- glfwMakeContextCurrent(WINDOW);

*/
#include <Core/PlatformDetection.h>

#include <memory>
#include <sstream>
#include <stdint.h>
#include <filesystem>

#ifdef LK_DEBUG
	#if defined(LK_PLATFORM_WINDOWS)
		#define LK_DEBUGBREAK() __debugbreak()
	#elif defined(LK_PLATFORM_LINUX)
		#include <signal.h>
		#define LK_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Debugbreak could not be implemented"
	#endif
	#define LK_ASSERTS_ENABLED
#else
	/* Release or Dist */
	#define LK_DEBUGBREAK()
#endif

#define LK_EXPAND_MACRO(x) x
#define LK_STRINGIFY_MACRO(x) #x

/* Bit field macro */
#define LK_BIT_FIELD(x) (1 << x)

#include <Core/Log.h>
namespace LukkelEngine {

	/* Reference using smart shared pointer */
	template<typename T>
	using ref = std::shared_ptr<T>;
	template<typename T, typename ... ARGS>
	constexpr ref<T> createRef(ARGS&& ... args)
	{
		return std::make_shared<T>(std::forward<ARGS>(args)...);
	}
}

#include <Core/Assert.h>
