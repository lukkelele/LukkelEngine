#pragma once

/* TODO: Insert precompiled header */
#include <memory>
#include <stdint.h>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

/* Assertion for debugging */
#ifdef LK_ASSERTS_ENABLED
	//
	#define LK_ASSERT(x) if (!(x)) __debugbreak();
	#define LK_INTERNAL_ASSERT_IMPL(type, check, msg, ...) { if(!(check)) { LK##type##ERROR(msg, __VA_ARGS__); LK_DEBUGBREAK(); } }
	#define LK_INTERNAL_ASSERT_WITH_MSG(type, check, ...) LK_INTERNAL_ASSERT_IMPL(type, check, "Assertion failed: {0}", __VA_ARGS__)
	#define LK_INTERNAL_ASSERT_NO_MSG(type, check) LK_INTERNAL_ASSERT_IMPL(type, check, "Assertion '{0}' failed at {1}:{2}", LK_STRINGIFY_MACRO(check), std::filesystem::path(__FILE__).filename().string(), __LINE__)
	#define LK_INTERNAL_ASSERT_GET_MACRO_NAME(arg1, arg2, macro, ...) macro
	#define LK_INTERNAL_ASSERT_GET_MACRO(...) LK_EXPAND_MACRO( LK_INTERNAL_ASSERT_GET_MACRO_NAME(__VA_ARGS__, LK_INTERNAL_ASSERT_WITH_MSG, LK_INTERNAL_ASSERT_NO_MSG) )
#else
	#define LK_ASSERT(...)
	#define LK_CORE_ASSERT(...)
#endif
