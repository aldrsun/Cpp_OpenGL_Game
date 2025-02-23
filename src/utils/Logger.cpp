#include "utils/Logger.h"


namespace Engine::Utils::Logger {

    void SetLogType(const LogType &log_type) {
        m_logType = log_type;
    }

    void m_LogToConsole(const char* message) {
        std::cout << message << std::endl;
    }

    void m_LogToFile(const char* message) {
        m_LogToConsole("[UNSUPPORTED LOG TYPE] ");
    }
} // namespace Engine::Utils::Logger