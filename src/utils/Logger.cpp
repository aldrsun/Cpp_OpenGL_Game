#include "utils/Logger.h"

namespace Utils {

    std::unordered_map<Logger::LogLevel, const char*> Logger::m_LogLevelPrefix = {
        {LogLevel::Log, "[LOG] "},
        {LogLevel::Debug, "[DEBUG] "},
        {LogLevel::Info, "[INFO] "},
        {LogLevel::Warning, "[WARNING] "},
        {LogLevel::Error, "[ERROR] "}
    };
    Logger::LogType Logger::s_logType = LogType::Console;

    void Logger::SetLogType(const LogType &log_type) {
        s_logType = log_type;
    }

    void Logger::m_LogToConsole(const char* message) {
        std::cout << message << std::endl;
    }

    void Logger::m_LogToFile(const char* message) {
        m_LogToConsole("[UNSUPPORTED LOG TYPE] ");
    }
} // namespace Engine::Utils::Logger