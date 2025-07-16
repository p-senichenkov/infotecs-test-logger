#pragma once

#include <fstream>
#include <iostream>
#include <ostream>

#include "logger.h"

namespace application {
std::ostream& AvailibleLevels(std::ostream& os);

/// @brief Demo application for Logger library
class Application {
private:
    std::ofstream ofs_;
    std::shared_ptr<logger::Logger> logger_;

public:
    Application();

    void Run();
};
}  // namespace application
