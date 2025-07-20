#include "logger.h"

#include <chrono>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "log_level.h"

namespace logger {
void Logger::Log(std::string&& msg, LogLevel level) {
    if (level == LogLevel::Default) {
        level = min_level_;
    } else if (static_cast<unsigned char>(level) < static_cast<unsigned char>(min_level_)) {
        return;
    }

    std::ostringstream oss;
    std::time_t const t_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    oss << '[' << std::put_time(std::localtime(&t_c), "%F %T") << "] (" << LogLevelToString(level)
        << ") " << msg << std::endl;
    writer_->Write(oss.str());
}
}  // namespace logger
