#ifndef LOGGER_H
#define LOGGER_H

#include <cstring>
#include <iostream>
#include <sstream>
#include <unordered_map>

namespace Utils {

    class Logger {
    public:
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

        static void SetLogType(const LogType& log_type);
        
        template<typename ... Params>
        static void Log(const LogLevel& log_level, const Params& ... params) {
            char buffer[s_bufferSize];
            char* p_cursor = buffer;
            std::snprintf(p_cursor, s_bufferSize, "%s", m_LogLevelPrefix[log_level]);
            p_cursor += std::strlen(m_LogLevelPrefix[log_level]);
    
            m_HandleLogParams(buffer, p_cursor, params...);
    
            std::cout << buffer << std::endl;
        }

        template<typename ... Params>
        static void Log(const Params& ... params) {
            Log(LogLevel::Log, params...);
        }

    private:
        static std::unordered_map<LogLevel, const char*> m_LogLevelPrefix;

        static const size_t s_bufferSize = 256;
        template<typename Param>
        static void m_HandleLogParams(char* buffer, char* p_cursor, const Param& param) {
            if constexpr (std::is_arithmetic_v<Param>) {
                std::snprintf(p_cursor, s_bufferSize - (p_cursor - buffer), "%g", static_cast<double>(param));
            } else if constexpr (std::is_same_v<Param, std::string>) {
                std::snprintf(p_cursor, s_bufferSize - (p_cursor - buffer), "%s", param.c_str());
            } else if constexpr (std::is_same_v<Param, const char*>) {
                std::snprintf(p_cursor, s_bufferSize - (p_cursor - buffer), "%s", param);
            } else {
                std::ostringstream oss;
                oss << param;
                std::snprintf(p_cursor, s_bufferSize - (p_cursor - buffer), "%s", oss.str().c_str());
            }
        }
    
        template<typename Param, typename ... Params>
        static void m_HandleLogParams(char* buffer, char* p_cursor, const Param& param, const Params& ... params) {
            m_HandleLogParams(buffer, p_cursor, param);
            p_cursor += std::strlen(p_cursor);
    
            *p_cursor = ' ';
            p_cursor ++;
            m_HandleLogParams(buffer, p_cursor, params ...);
        }

        static LogType s_logType; // TODO : WILL BE IMPROVED
        static void m_LogToConsole(const char* message);
        static void m_LogToFile(const char* message);
    };
} // Engine::Utils::Logger

#endif // LOGGER_H
