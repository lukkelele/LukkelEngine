#include "LKpch.h"
#include "LukkelEngine/Core/LukkeLog.h"

namespace LukkelEngine {

	std::shared_ptr<spdlog::logger> LukkeLog::s_CoreLogger;
	std::shared_ptr<spdlog::logger> LukkeLog::s_ClientLogger;

	void LukkeLog::init(std::string logfilename,
		           std::string coreLoggerName,
			       std::string clientLoggerName)
	{
		std::vector<spdlog::sink_ptr> logSinks;
		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(logfilename, true));

		logSinks[0]->set_pattern(" %^%H:%M:%S | %n: %v%$");
		logSinks[1]->set_pattern(" %H:%M:%S | %n: %v%$");

		s_CoreLogger = std::make_shared<spdlog::logger>(coreLoggerName, begin(logSinks), end(logSinks));
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);

		s_ClientLogger = std::make_shared<spdlog::logger>(clientLoggerName, begin(logSinks), end(logSinks));
		spdlog::register_logger(s_ClientLogger);
		s_ClientLogger->set_level(spdlog::level::trace);
		s_ClientLogger->flush_on(spdlog::level::trace);
	}


}
