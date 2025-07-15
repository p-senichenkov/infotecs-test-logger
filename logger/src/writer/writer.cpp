#include "writer/writer.h"

#include <chrono>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>

using namespace std::chrono_literals;

namespace logger::writer {
// Period at which Writer wakes up to check if it should stop
std::chrono::milliseconds const Writer::kWakeUpPeriod = 250ms;
// Time Writer sleeps after each write to allow pushing new messages to the queue
std::chrono::milliseconds const Writer::kWriteTime = 50ms;

void Writer::Write(std::string&& msg) {
    {
        std::lock_guard guard{queue_mutex_};
        queue_.push(std::move(msg));
    }
    cv_.notify_one();
}

void Writer::Run() {
    std::unique_lock lk{queue_mutex_};
    while (run_ || !queue_.empty()) {
        // Wake up sometimes to check `run_`
        cv_.wait_for(lk, kWakeUpPeriod);

        if (queue_.empty()) {
            // Woke up to check `run_` (or spurious wake up, which is safe here)
            continue;
        }

        auto msg = queue_.front();
        write_strategy_->Write(msg);
        queue_.pop();
        lk.unlock();
        std::this_thread::sleep_for(kWriteTime);
        lk.lock();
    }
}
}  // namespace logger::writer
