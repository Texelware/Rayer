#pragma once

#include <rpch.h>

namespace Rayer {

	enum class LogLevel {
		NONE = 0,
		LOG_LEVEL_WARN,
		LOG_LEVEL_ERROR,
		LOG_LEVEL_INFO,

	};

	struct Log {

		LogLevel level;
		std::string message;

	};

	class LogManager {

	public:

		static LogManager* Get() {

			if (instance == nullptr) {

				instance = new LogManager;
				return instance;
			}

			else {

				return instance;
			}

		}

		void ClearLogs() {

			if (!logs.empty()) {

				logs.clear();

			}

		}

		void AddLog(Log log) {

			logs.push_back(log);

		}

		std::vector<Log>::iterator GetLogsBegin() { return logs.begin(); }
		std::vector<Log>::iterator GetLogsEnd() { return logs.end(); }


	private:

		LogManager() = default;


		std::vector<Log> logs {};

		static LogManager* instance;
	};

}