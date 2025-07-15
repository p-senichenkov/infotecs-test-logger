#pragma once

#include <string>

namespace logger::writer {
// Represents different low-level write methods
class WriteStrategy {
public:
    virtual ~WriteStrategy() = default;
    virtual void Write(std::string const& msg) = 0;
};
}  // namespace logger::writer
