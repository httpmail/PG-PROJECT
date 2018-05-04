#include "PGUtil.h"

#include <chrono>

namespace PG {

    std::time_t GetTimeStamp()
    {
        using namespace std::chrono;
        return system_clock::to_time_t(system_clock::now());
    }
}