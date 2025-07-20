#include "logger_tests.h"

#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "log_level.h"
#include "logger.h"
#include "writer/write_to_stream.h"
#include "writer/writer.h"

namespace test::logger {
using namespace ::logger;
using namespace ::logger::writer;

bool LoggerTest(LogLevel default_lvl, std::vector<MsgDescription> const& msgs) {
    std::stringstream ss;
    auto writer = std::make_unique<Writer>(std::make_unique<WriteToStream>(ss));
    Logger logger{std::move(writer), default_lvl};

    for (auto const& [text, log_level, _] : msgs) {
        if (log_level == LogLevel::Default) {
            logger.Log(text);
        } else {
            logger.Log(text, log_level);
        }
    }

    logger.Stop();

    // Check
    using MsgPair = std::pair<std::string, LogLevel>;
    for (auto [msg, lvl, print] : msgs) {
        if (!print) {
            continue;
        }

        // Timestamp constists of two separate parts.
        // Both need to be skipped
        std::string str;
        ss >> str;
        ss >> str;

        // Check log level
        ss >> str;
        if (lvl == LogLevel::Default) {
            lvl = default_lvl;
        }
        if (str != '(' + LogLevelToString(lvl) + ')') {
            std::cout << "Wrong log level: " << str << '\n';
            return false;
        }

        // Skip whitespace
        ss.ignore();

        // Check message
        std::getline(ss, str);
        if (str != msg) {
            std::cout << "Wrong message: '" << str << "'\n";
            return false;
        }
    }
    return true;
}

bool AllMessages() {
    return LoggerTest(LogLevel::Info, {{"info_msg", LogLevel::Info, true},
                                       {"warn_msg", LogLevel::Warn, true},
                                       {"error_msg", LogLevel::Error, true}});
}

bool OnlyImportantMessages() {
    return LoggerTest(LogLevel::Warn, {{"info_msg", LogLevel::Info, false},
                                       {"warn_msg", LogLevel::Warn, true},
                                       {"error_msg", LogLevel::Error, true}});
}

bool NoMessages() {
    std::stringstream ss;
    auto writer = std::make_unique<Writer>(std::make_unique<WriteToStream>(ss));
    Logger logger{std::move(writer), LogLevel::Error};

    logger.Log("info_msg", LogLevel::Info);
    logger.Log("warn_msg", LogLevel::Warn);

    logger.Stop();

    return ss.str().empty();
}

bool DefaultLevel() {
    return LoggerTest(LogLevel::Warn, {{"info_msg", LogLevel::Info, false},
                                       {"default_msg", LogLevel::Default, true}});
}
}  // namespace test::logger
