#pragma once

#include <memory>
#include <stdint.h>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "LukkelEngine/Core/LukkeLog.h"

#ifdef LK_DEBUG
	#if defined(LK_PLATFORM_WINDOWS)
		#define LK_DEBUGBREAK __debugbreak()
	#elif defined(LK_PLATFORM_LINUX)
		#include <signal.h>
		#define LK_DEBUGBREAK raise(SIGTRAP)
		#ifndef LK_DEBUGBREAK
			#define __debugbreak() \
				asm("0:"                              \
					".pushsection embed-breakpoints;" \
					".quad 0b;"                       \
					".popsection;")
		#endif
	#else
		#error "Debugbreak could not be implemented"
	#endif
	#define LK_ASSERTS_ENABLED
#else
	/* Release or Dist */
	#define LK_DEBUGBREAK()
#endif

/* Assertion for debugging */
#ifdef LK_ASSERTS_ENABLED
	// #define LK_ASSERT(x) if (!(x)) __debugbreak();
	#define LK_ASSERT_MESSAGE(...) ::LukkelEngine::LukkeLog::PrintMessage(::LukkelEngine::LukkeLog::LK_ASSERT_LEVEL::CRITICAL, __VA_ARGS__)
	#define LK_ASSERT(condition, ...) { if (!(condition)) { LK_ASSERT_MESSAGE(__VA_ARGS__); LK_DEBUGBREAK; } }
#else
	#define LK_ASSERT(...)
#endif
