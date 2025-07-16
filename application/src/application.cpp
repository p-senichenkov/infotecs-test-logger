#include "application.h"

#include <fstream>
#include <memory>
#include <ostream>
#include <string>

#include "log_level.h"
#include "logger.h"
#include "writer/write_to_stream.h"

using namespace logger;

namespace application {
std::ostream& AvailibleLevels(std::ostream& os) {
    for (auto it = kLevels.begin(); it != kLevels.end(); it++) {
        if (it != kLevels.begin()) {
            std::cout << ", ";
        }
        std::cout << *it;
    }
    return os;
}

Application::Application() {
    std::cout << "Select minimum log level (availible levels: " << AvailibleLevels << "): ";
    std::string level;
    std::cin >> level;
    auto min_level = LogLevelFromString(std::move(level));

    std::cout << "Select log file name: ";
    std::string filename;
    std::cin >> filename;

    std::ofstream ofs{filename};
    auto writer = std::make_unique<writer::Writer>(std::make_unique<writer::WriteToStream>(ofs));
    logger_ = std::make_unique<Logger>(std::move(writer), min_level);
}

void Application::Run() {
    while (std::cin.good()) {
        std::cout << "Select log level (availible levels: " << AvailibleLevels << "): ";
        std::string level;
        std::cin >> level;

        std::cout << "Enter message ('q' to quit): ";
        std::string msg;
        // Skip extra newline from previous input
        std::getline(std::cin, msg);
        std::getline(std::cin, msg);

        if (msg == std::string("q")) {
            break;
        }
        logger_->Log(std::move(msg),
                     level.empty() ? LogLevel::Default : LogLevelFromString(std::move(level)));
    }

    std::cout << "Quitting...";
}
}  // namespace application
