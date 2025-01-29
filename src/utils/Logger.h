#ifndef LOGGER_H
#define LOGGER_H

#include <string>

namespace Utils {
    class Logger {
    public:
        static void Log(const std::string& message);
    };
} // namespace Engine::Utils

#endif