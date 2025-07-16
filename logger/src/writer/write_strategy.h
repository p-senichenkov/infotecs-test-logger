#pragma once

#include <string>

namespace logger::writer {
/// @brief Represents different low-level @c write methods
class WriteStrategy {
public:
    virtual ~WriteStrategy() = default;
    virtual void Write(std::string const& msg) = 0;
};
}  // namespace logger::writer
