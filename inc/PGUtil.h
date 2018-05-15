#pragma once

#include <ctime>
#include <string>
#include <chrono>

#define PG_ARRAY_SIZE(arr)  (sizeof(arr) / sizeof(arr[0]))

namespace PG {

    std::chrono::time_point<std::chrono::system_clock> GetTimeStamp();

    std::string  Timestamp2Str(const std::chrono::time_point<std::chrono::system_clock> &tp,
        const char* fmt = "%F %T");

    std::string Timestamp2StrMilliseconds(const std::chrono::time_point<std::chrono::system_clock> &tp, 
        const char* fmt = "%F %T");

    int     GenerateRandomNumber(int left, int right);
    double  GenerateRandomNumber(double left, double right);
    double  Generate01Random();
}