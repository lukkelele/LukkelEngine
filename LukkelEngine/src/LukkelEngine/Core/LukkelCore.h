#pragma once
/* 
	LukkelEngine core file.
	Holds platform specific details and macros.

	> GLFW
		The GLCall macro does not function on some OpenGL functions.
		Debugging can be a pain when the macro is seen as trivial but it can be prone to errors.
		Specific ones to watch out for:
			- glfwMakeContextCurrent(WINDOW);

*/

#include <Core/PlatformDetection.h>

#include <memory>
#include <sstream>
#include <cstdint>

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

/* Bit field macro */
#define LK_BIT_FIELD(x) (1 << x)

namespace LukkelEngine {

	/* Reference using smart shared pointer */
	template<typename L>
	using ref = std::shared_ptr<L>;
	template<typename L, typename ... ARGS>
	constexpr ref<L> createRef(ARGS&& ... args)
	{
		return std::make_shared<L>(std::forward<ARGS>(args)...);
	}
}
