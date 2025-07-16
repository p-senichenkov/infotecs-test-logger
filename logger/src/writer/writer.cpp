#include "writer/writer.h"

#include <chrono>
#include <mutex>
#include <queue>
#include <thread>

using namespace std::chrono_literals;

namespace logger::writer {
std::chrono::milliseconds const Writer::kWakeUpPeriod = 250ms;

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
        queue_.pop();
        lk.unlock();
        write_strategy_->Write(msg);
        lk.lock();
    }
}
}  // namespace logger::writer
