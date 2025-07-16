#pragma once

#include <iostream>
#include <ostream>

#include "logger.h"

namespace application {
std::ostream& AvailibleLevels(std::ostream& os);

// Demo application for Logger library
class Application {
private:
	std::shared_ptr<logger::Logger> logger_;

public:
    Application();

    void Run();
};
}  // namespace application
