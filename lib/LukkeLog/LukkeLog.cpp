#include "LukkeLog.h"

namespace LukkeLog {

	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	#ifdef LKLOG_CLIENT_ENABLE
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;
	#endif

	void Log::init(std::string logfilename,
		           std::string coreLoggerName,
			       std::string clientLoggerName)
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(logfilename, true));

		logSinks[0]->set_pattern("%^[%T] %n: %v%$");
		logSinks[1]->set_pattern("[%T] [%l] %n: %v");

		s_CoreLogger = std::make_shared<spdlog::logger>(coreLoggerName, begin(logSinks), end(logSinks));
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

#ifdef LKLOG_CLIENT_ENABLE
		s_ClientLogger = std::make_shared<spdlog::logger>(clientLoggerName, begin(logSinks), end(logSinks));
		spdlog::register_logger(s_ClientLogger);
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->flush_on(spdlog::level::trace);
#endif
	}
}