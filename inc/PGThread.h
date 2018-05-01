#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>

namespace PG {
    using MutexLockGuard = std::lock_guard<std::mutex>;
    using ConditionLock  = std::unique_lock<std::mutex>;
}