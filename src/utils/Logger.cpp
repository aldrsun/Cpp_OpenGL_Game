#include "Logger.h"
#include <iostream>

namespace Utils {
    void Logger::Log(const std::string& message) {
        std::cout << "[LOG] " << message << std::endl;
    }
} // namespace Utils