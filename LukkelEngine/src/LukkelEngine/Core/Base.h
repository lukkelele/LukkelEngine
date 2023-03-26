#pragma once
/* 
	LukkelEngine base file.
*/

#include "LukkelEngine/Core/PlatformDetection.h"

#include <stdint.h>
#include <filesystem>

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
