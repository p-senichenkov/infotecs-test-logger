#pragma once

#include <memory>
#include <stdexcept>
#include <string>
#include <thread>

#include "log_level.h"
#include "writer/writer.h"

namespace logger {
/// @brief The logger itself.
/// It is paramethrized with concrete Writer.
class Logger {
private:
    std::unique_ptr<writer::Writer> writer_;
    LogLevel min_level_;

    std::thread writing_thread_;

    bool stopped_ = false;

public:
    Logger() = default;

    ~Logger() {
        Stop();
    }

    Logger(std::unique_ptr<writer::Writer>&& writer, LogLevel min_level)
        : writer_(std::move(writer)), min_level_(min_level) {
        if (min_level_ == LogLevel::Default) {
            throw std::logic_error("Tried to use Default log level as minimum log level");
        }
        writing_thread_ = std::thread(&writer::Writer::Run, writer_.get());
    }

    void SetMinLogLevel(LogLevel new_min_lelel) {
        min_level_ = new_min_lelel;
    }

    void Log(std::string const& msg, LogLevel level = LogLevel::Default);

    /// @brief Stop receiving messages.
    /// Logger actually stops after all messages are flushed.
    /// Destructor acts the same way.
    void Stop() {
        if (stopped_) {
            return;
        }

        writer_->Stop();
        if (!writing_thread_.joinable()) {
            throw std::logic_error("Writing thread is not joinable.");
        }
        writing_thread_.join();
        stopped_ = true;
    }
};
}  // namespace logger
