#ifndef LOGGER_H
#define LOGGER_H

#include <cstring>
#include <iostream>
#include <sstream>
#include <unordered_map>

namespace Utils::Logger {
    enum class LogType {
        Console,
        File,
        ConsoleAndFile,
    };

    enum class LogLevel {
        Log,
        Debug,
        Info,
        Warning,
        Error
    };

    void SetLogType(const LogType& log_type);

    inline std::unordered_map<LogLevel, const char*> LogLevelPrefix = {
        {LogLevel::Log, "[LOG] "},
        {LogLevel::Debug, "[DEBUG] "},
        {LogLevel::Info, "[INFO] "},
        {LogLevel::Warning, "[WARNING] "},
        {LogLevel::Error, "[ERROR] "}
    };

    template<typename T>
    void Log(const T& value, const LogLevel& log_level = LogLevel::Log) {
        constexpr size_t BUFFER_SIZE = 256;
        char buffer[BUFFER_SIZE];

        char* ptr = buffer;
        std::snprintf(ptr, BUFFER_SIZE, "%s", LogLevelPrefix[log_level]);
        ptr += std::strlen(LogLevelPrefix[log_level]);

        if constexpr (std::is_arithmetic_v<T>) {
            std::snprintf(ptr, BUFFER_SIZE - (ptr - buffer), "%g", static_cast<double>(value));
        } else if constexpr (std::is_same_v<T, std::string>) {
            std::snprintf(ptr, BUFFER_SIZE - (ptr - buffer), "%s", value.c_str());
        } else if constexpr (std::is_same_v<T, const char*>) {
            std::snprintf(ptr, BUFFER_SIZE - (ptr - buffer), "%s", value);
        } else {
            std::ostringstream oss;
            oss << value;
            std::snprintf(ptr, BUFFER_SIZE - (ptr - buffer), "%s", oss.str().c_str());
        }

        std::cout << buffer << std::endl;
    }

    inline LogType m_logType = LogType::Console;

    void m_LogToConsole(const char* message);
    void m_LogToFile(const char* message);
} // Engine::Utils::Logger

#endif // LOGGER_H
