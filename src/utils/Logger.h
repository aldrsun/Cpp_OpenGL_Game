#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace Utils {
    class Logger {
    public:
        enum class LogType {
            Console,
            File,
            ConsoleAndFile,
        };

        enum class LogLevel {
            Info,
            Warning,
            Error
        };

        static void SetLogType(const LogType& log_type);
        static void Log(const std::string& message, const LogLevel& log_level = LogLevel::Info);

    private:
        static LogType m_logType;
        static void m_LogToConsole(const std::string& message);
        static void m_LogToFile(const std::string& message);
    };
} // Utils

#endif // LOGGER_H
