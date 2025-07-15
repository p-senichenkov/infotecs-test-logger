#pragma once

#include <string>
#include <vector>

namespace logger {
enum class LogLevel { Default, Info, Warn, Error };

static std::vector<std::string> const kLevels{"Info", "Warn", "Error"};

std::string LogLevelToString(LogLevel level);

LogLevel LogLevelFromString(std::string&& str);
}  // namespace logger
