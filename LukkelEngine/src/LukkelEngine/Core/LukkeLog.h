/*
	LukkeLog
	---------------------------------
	Simple logger using spdlog.

	Preprocessor definitions:
	LKLOG_ADVANCED - implements more advanced logging functionality but is not as lightweight
	LKLOG_CLIENT_ENABLE - enable a second client logger

*/
#ifndef _LUKKELOG_H
#define _LUKKELOG_H

#include <stdint.h>
#include <cstring>

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)
// Needed for terminal
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include "glm/glm.hpp"
#include <glm/gtx/string_cast.hpp>

namespace LukkeLog {

	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:
		static void init(std::string logfileName = "LukkeLog.log",
						 std::string coreLoggerName = "CORE",
						 std::string clientLoggerName = "CLIENT");

		static std::shared_ptr<spdlog::logger>& getCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& getClientLogger() { return s_ClientLogger; }

		static void printVec3(glm::vec3& vector);
	};
}


#define LKLOG_VEC3(...)					::LukkeLog::Log::printVec3(__VA_ARGS__)

/* Core log macros */
#define LKLOG_INFO(...)    				::LukkeLog::Log::getCoreLogger()->trace(__VA_ARGS__)
#define LKLOG_TRACE(...)     			::LukkeLog::Log::getCoreLogger()->debug(__VA_ARGS__)
#define LKLOG_WARN(...)     			::LukkeLog::Log::getCoreLogger()->warn(__VA_ARGS__)
#define LKLOG_ERROR(...)    			::LukkeLog::Log::getCoreLogger()->error(__VA_ARGS__)
#define LKLOG_CRITICAL(...) 			::LukkeLog::Log::getCoreLogger()->critical(__VA_ARGS__)

/* Client log macros */
#define LKLOG_CLIENT_INFO(...)			::LukkeLog::Log::getClientLogger()->trace(__VA_ARGS__)
#define LKLOG_CLIENT_TRACE(...)         ::LukkeLog::Log::getClientLogger()->debug(__VA_ARGS__)
#define LKLOG_CLIENT_WARN(...)          ::LukkeLog::Log::getClientLogger()->warn(__VA_ARGS__)
#define LKLOG_CLIENT_ERROR(...)         ::LukkeLog::Log::getClientLogger()->error(__VA_ARGS__)
#define LKLOG_CLIENT_CRITICAL(...)      ::LukkeLog::Log::getClientLogger()->critical(__VA_ARGS__)


#endif /* _LUKKELOG_H */