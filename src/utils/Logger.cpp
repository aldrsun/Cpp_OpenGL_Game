#include "Logger.h"
#include <iostream>

namespace Utils {
    Logger::LogType Logger::m_logType = LogType::Console;

    void Logger::SetLogType(const LogType &log_type) {
        m_logType = log_type;
    }

    void Logger::Log(const std::string& message, const LogLevel& log_level) {
        std::string log_message;
        switch (log_level) {
            case LogLevel::Info:
                log_message = "[INFO] " + message;
                break;
            case LogLevel::Warning:
                log_message = "[WARNING] " + message;
                break;
            case LogLevel::Error:
                log_message = "[ERROR] " + message;
                break;
            default:
                log_message = "[UNSUPPORTED LOG LEVEL] " + message;
                break;
        }

        switch (m_logType) {
            case LogType::Console:
                m_LogToConsole(log_message);
                break;
            case LogType::File:
                m_LogToFile(log_message);
                break;
            case LogType::ConsoleAndFile:
                m_LogToConsole(log_message);
                m_LogToFile(log_message);
                break;
        }
    }

    void Logger::m_LogToConsole(const std::string &message) {
        std::cout << message << std::endl;
    }
    void Logger::m_LogToFile(const std::string &message) {
        m_LogToConsole("[UNSUPPORTED LOG TYPE] " + message);
    }

} // namespace Utils