#pragma once

#include <chrono>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>
#include <string>

#include "writer/write_strategy.h"

namespace logger::writer {
class Writer {
private:
    static std::chrono::milliseconds const kWakeUpPeriod;
    static std::chrono::milliseconds const kWriteTime;

    std::unique_ptr<WriteStrategy> write_strategy_;

    std::queue<std::string> queue_;
    bool run_ = true;

    std::condition_variable cv_;
    mutable std::mutex queue_mutex_;

public:
    Writer(std::unique_ptr<WriteStrategy>&& write_strategy)
        : write_strategy_(std::move(write_strategy)) {}

    ~Writer() {
        Stop();
    }

    void Write(std::string&& msg);

    void Run();

    void Stop() {
        run_ = false;
    }
};
}  // namespace logger::writer
