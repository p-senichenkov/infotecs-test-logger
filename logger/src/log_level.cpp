#include "log_level.h"

#include <algorithm>
#include <cctype>
#include <stdexcept>
#include <string>

namespace logger {
std::string LogLevelToString(LogLevel level) {
    switch (level) {
        case LogLevel::Default:
            throw std::logic_error("Tried to convert Default log level to string");
        case LogLevel::Info:
            return "INFO";
        case LogLevel::Warn:
            return "WARN";
        case LogLevel::Error:
            return "ERROR";
    }
}

LogLevel LogLevelFromString(std::string&& str) {
    std::transform(str.begin(), str.end(), str.begin(), [](char ch) { return std::tolower(ch); });

    if (str == "info") {
        return LogLevel::Info;
    }
    if (str == "warn") {
        return LogLevel::Warn;
    }
    if (str == "error") {
        return LogLevel::Error;
    }
    throw std::logic_error("Unknown log level: " + str);
}
}  // namespace logger
