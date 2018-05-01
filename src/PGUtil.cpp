#include "PGUtil.h"

#include <chrono>

namespace PG {
    using TP_MILLISECONDS = std::chrono::time_point < std::chrono::high_resolution_clock, std::chrono::milliseconds>;
    using TP_MICROSECONDS = std::chrono::time_point < std::chrono::high_resolution_clock, std::chrono::microseconds>;

    std::time_t GetMilliTimeStamp()
    {
        TP_MILLISECONDS tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now());
        return tp.time_since_epoch().count();
    }

    std::time_t GetMicroTimeStamp()
    {
        TP_MICROSECONDS tp = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now());
        return tp.time_since_epoch().count();
    }
}