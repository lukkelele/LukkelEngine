#include <Core/LukkelCore.h>
#include <stdint.h>
#include <cstring>
#include <memory>
#include <sstream>
#include <cstdint>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/gtx/string_cast.hpp"

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace LukkelEngine {

	class Log
	{
	public:
		static void init();
		static ref<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
		static ref<spdlog::logger>& getClientLogger() { return s_ClientLogger; }
	private:
		static ref<spdlog::logger> s_CoreLogger;
		static ref<spdlog::logger> s_ClientLogger;
	};

}

template<typename OStream, glm::length_t L, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::vec<L, T, Q>& vector)
{
	return os << glm::to_string(vector);
}

template<typename OStream, glm::length_t C, glm::length_t R, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, const glm::mat<C, R, T, Q>& matrix)
{
	return os << glm::to_string(matrix);
}

template<typename OStream, typename T, glm::qualifier Q>
inline OStream& operator<<(OStream& os, glm::qua<T, Q> quaternion)
{
	return os << glm::to_string(quaternion);
}

/* Core log macros */
#define LK_CORE_TRACE(...)    ::LukkelEngine::Log::getCoreLogger()->trace(__VA_ARGS__)
#define LK_CORE_INFO(...)     ::LukkelEngine::Log::getCoreLogger()->info(__VA_ARGS__)
#define LK_CORE_WARN(...)     ::LukkelEngine::Log::getCoreLogger()->warn(__VA_ARGS__)
#define LK_CORE_ERROR(...)    ::LukkelEngine::Log::getCoreLogger()->error(__VA_ARGS__)
#define LK_CORE_CRITICAL(...) ::LukkelEngine::Log::getCoreLogger()->critical(__VA_ARGS__)

/* Client log macros */
#define LK_TRACE(...)         ::LukkelEngine::Log::getClientLogger()->trace(__VA_ARGS__)
#define LK_INFO(...)          ::LukkelEngine::Log::getClientLogger()->info(__VA_ARGS__)
#define LK_WARN(...)          ::LukkelEngine::Log::getClientLogger()->warn(__VA_ARGS__)
#define LK_ERROR(...)         ::LukkelEngine::Log::getClientLogger()->error(__VA_ARGS__)
#define LK_CRITICAL(...)      ::LukkelEngine::Log::getClientLogger()->critical(__VA_ARGS__)