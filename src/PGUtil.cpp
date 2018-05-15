#include "PGUtil.h"

#include <chrono>
#include <iomanip>
#include <sstream>

#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/uniform_01.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/mersenne_twister.hpp>

namespace PG {

    using random_generator  =  boost::mt19937;
    using int_random_type   = boost::uniform_int<>;
    using real_random_type  = boost::uniform_real<>;
    using real_01_type      = boost::uniform_01<>;

    static random_generator sGenerator(static_cast<uint32_t>(std::chrono::system_clock::to_time_t(GetTimeStamp())));

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

    int GenerateRandomNumber(int left, int right)
    {
        int_random_type int_random(left, right);
        boost::variate_generator<random_generator&, int_random_type > deg(sGenerator, int_random);
        return deg();
    }

    double GenerateRandomNumber(double left, double right)
    {
        real_random_type real_random(left, right);
        boost::variate_generator<random_generator&, real_random_type > deg(sGenerator, real_random);
        return deg();
    }

    double Generate01Random()
    {
        real_01_type real_random;
        boost::variate_generator<random_generator&, real_01_type > deg(sGenerator, real_random);
        return deg();
    }
}