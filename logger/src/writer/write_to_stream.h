#pragma once

#include <iostream>
#include <ostream>
#include <string>

#include "writer/write_strategy.h"

namespace logger::writer {
// Provides interface to write to any kind of `std::ostream`
class WriteToStream : public WriteStrategy {
private:
    std::ostream* os_;

public:
    WriteToStream(std::ostream& os) : os_(&os) {}

    virtual void Write(std::string const& msg) override {
        *os_ << msg;
    }
};
}  // namespace logger::writer
