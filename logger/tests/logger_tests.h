#pragma once

#include <string>

#include "log_level.h"
#include "test.h"

namespace test {
namespace logger {
struct MsgDescription {
    std::string text;
    ::logger::LogLevel log_level;
    bool should_be_printed;
};

bool LoggerTest(::logger::LogLevel default_lvl, std::vector<MsgDescription> const& msgs);
bool AllMessages();
bool OnlyImportantMessages();
bool NoMessages();
bool DefaultLevel();
}  // namespace logger

static std::vector<Test> logger_tests{{"All messages", logger::AllMessages},
                                      {"Only important messages", logger::OnlyImportantMessages},
                                      {"No messages", logger::NoMessages},
                                      {"Default log level", logger::DefaultLevel}};
}  // namespace test
