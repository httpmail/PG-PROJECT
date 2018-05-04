#include "PGUtil.h"

#include <chrono>
#include <iomanip>
#include <sstream>

namespace PG {

    std::chrono::time_point<std::chrono::system_clock> GetTimeStamp()
    {
        using namespace std::chrono;
        return system_clock::now();
    }

    std::string Timestamp2Str(const std::chrono::time_point<std::chrono::system_clock> &tp, 
        const char* fmt /*= "%F %T"*/)
    {
        using namespace std::chrono;

        std::stringstream timestampStream;
        std::tm t;
        std::time_t timestamp = system_clock::to_time_t(system_clock::now());
        localtime_s(&t, &timestamp);
 
        auto timeobject = std::put_time(&t, fmt);
        timestampStream << timeobject;

        return timestampStream.str();
    }

    std::string Timestamp2StrMilliseconds(const std::chrono::time_point<std::chrono::system_clock> &tp, 
        const char* fmt /*= "%F %T"*/)
    {
        using namespace std::chrono;

        std::stringstream timestampStream;
        std::tm t;
        std::time_t timestamp = system_clock::to_time_t(system_clock::now());
        localtime_s(&t, &timestamp);

        auto timeobject = std::put_time(&t, fmt);
        timestampStream << timeobject;

        std::tm t1;
        timestampStream >> std::get_time(&t1, fmt);
        auto after = system_clock::from_time_t(std::mktime(&t));

        duration<float> diff = tp - after;

        timestampStream.clear();
        timestampStream << ":" << std::setw(7) << std::left << std::setprecision(6) <<std::setfill('0')<< diff.count() * 1000;

        return timestampStream.str();
    }
}