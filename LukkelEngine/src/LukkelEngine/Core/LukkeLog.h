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

#include "LukkelEngine/Core/Base.h"
#include <stdint.h>
#include <cstring>

// This ignores all warnings raised inside External headers
#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/fmt/fmt.h>
#pragma warning(pop)
// Needed for terminal
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include "glm/glm.hpp"
#include <glm/gtx/string_cast.hpp>

namespace LukkelEngine {

	class LukkeLog
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	public:

		static enum class LK_ASSERT_LEVEL
		{
			INFO, TRACE, WARN, ERR, CRITICAL
		};

		static void Init(std::string logfileName = "LukkeLog.log",
						 std::string coreLoggerName = "CORE",
						 std::string clientLoggerName = "CLIENT");

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

		static void PrintVec3(glm::vec3& vector);

		template<typename... ARGS>
		static void PrintMessage(LK_ASSERT_LEVEL level, ARGS&&... args);


	};

	// FIXME: fmt::v9::format error when trying to parse passed __VA_ARGS__
	template<typename... ARGS>
	void LukkeLog::PrintMessage(LK_ASSERT_LEVEL level, ARGS&&... args)
	{
		auto logger = GetCoreLogger();
		// auto str = fmt::format(std::forward<ARGS>(args)...);
		switch (level)
		{
			case LK_ASSERT_LEVEL::INFO:
				// logger->info("{0}", fmt::format(std::forward<ARGS>(args)...));
				break;
			case LK_ASSERT_LEVEL::CRITICAL:
				// logger->critical("{0}", fmt::format(std::forward<ARGS>(args)...));
				logger->critical("{0}", "Assertion failed");
				break;
		}
	}

}

/* Core log macros */
#define LKLOG_INFO(...)    				::LukkelEngine::LukkeLog::GetCoreLogger()->trace(__VA_ARGS__)
#define LKLOG_TRACE(...)     			::LukkelEngine::LukkeLog::GetCoreLogger()->debug(__VA_ARGS__)
#define LKLOG_WARN(...)     			::LukkelEngine::LukkeLog::GetCoreLogger()->warn(__VA_ARGS__)
#define LKLOG_ERROR(...)    			::LukkelEngine::LukkeLog::GetCoreLogger()->error(__VA_ARGS__)
#define LKLOG_CRITICAL(...) 			::LukkelEngine::LukkeLog::GetCoreLogger()->critical(__VA_ARGS__)

/* Client log macros */
#define LKLOG_CLIENT_INFO(...)			::LukkelEngine::LukkeLog::GetClientLogger()->trace(__VA_ARGS__)
#define LKLOG_CLIENT_TRACE(...)         ::LukkelEngine::LukkeLog::GetClientLogger()->debug(__VA_ARGS__)
#define LKLOG_CLIENT_WARN(...)          ::LukkelEngine::LukkeLog::GetClientLogger()->warn(__VA_ARGS__)
#define LKLOG_CLIENT_ERROR(...)         ::LukkelEngine::LukkeLog::GetClientLogger()->error(__VA_ARGS__)
#define LKLOG_CLIENT_CRITICAL(...)      ::LukkelEngine::LukkeLog::GetClientLogger()->critical(__VA_ARGS__)


#endif /* _LUKKELOG_H */