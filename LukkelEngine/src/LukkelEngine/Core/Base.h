#pragma once
/* 
	LukkelEngine base file.
*/

#include "LukkelEngine/Core/PlatformDetection.h"

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

// Draw modes
#define LK_DRAW_FILL 0
#define LK_DRAW_LINE 1

#define LK_EXPAND_MACRO(x) x
#define LK_STRINGIFY_MACRO(x) #x

// Bit field macro
#define LK_BIT_FIELD(x) (1 << x)

// Bind event
#define LK_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace LukkelEngine {

	/* Unique pointer */
	template<typename T>
	using u_ptr = std::unique_ptr<T>;
	template<typename T, typename ... ARGS>
	constexpr u_ptr<T> create_u_ptr(ARGS&& ... args)
	{
		return std::make_unique<T>(std::forward<ARGS>(args)...);
	}

	/* Reference using smart shared pointer */
	template<typename T>
	using s_ptr = std::shared_ptr<T>;
	template<typename T, typename ... ARGS>
	constexpr s_ptr<T> create_s_ptr(ARGS&& ... args)
	{
		return std::make_shared<T>(std::forward<ARGS>(args)...);
	}
}

#include "LukkelEngine/Core/LukkeLog.h"
#include "LukkelEngine/Core/Assert.h"
