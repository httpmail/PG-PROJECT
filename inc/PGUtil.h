#pragma once

#include <ctime>
#include <string>
#include <chrono>

namespace PG {
    std::chrono::time_point<std::chrono::system_clock> GetTimeStamp();

    std::string  Timestamp2Str(const std::chrono::time_point<std::chrono::system_clock> &tp,
        const char* fmt = "%F %T");

    std::string Timestamp2StrMilliseconds(const std::chrono::time_point<std::chrono::system_clock> &tp, 
        const char* fmt = "%F %T");
}