#pragma once

#include <string>
#include <vector>

namespace logger {
/// @note @c Default level is for technical use only.
/// Message with Default log level cannot be created.
enum class LogLevel { Default, Info, Warn, Error };

/// @brief Availible log levels.
/// Mainly used in user hints in CLI.
static std::vector<std::string> const kLevels{"Info", "Warn", "Error"};

std::string LogLevelToString(LogLevel level);

LogLevel LogLevelFromString(std::string&& str);
}  // namespace logger
