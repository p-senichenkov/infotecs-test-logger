#pragma once

#include <chrono>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <string>

#include "writer/write_strategy.h"

namespace logger::writer {
/// @brief Represents single "writing thread" which handles message queue and can be
/// instantiated with concrete @c WritingStrategy
class Writer {
private:
    // Period at which Writer wakes up to check if it should stop
    static std::chrono::milliseconds const kWakeUpPeriod;

    std::unique_ptr<WriteStrategy> write_strategy_;

    std::queue<std::string> queue_;
    bool run_ = true;

    std::condition_variable cv_;
    mutable std::mutex queue_mutex_;

public:
    Writer(std::unique_ptr<WriteStrategy>&& write_strategy)
        : write_strategy_(std::move(write_strategy)) {}

    /// @brief Save message to the queue
    void Write(std::string&& msg);

    /// @brief Start writing saved messages.
    /// Better call it in a separate thread.
    void Run();

    /// @brief Stop waiting for new messages.
    /// Writer will be actually stopped when all messages will be written.
    void Stop() {
        run_ = false;
    }
};
}  // namespace logger::writer
