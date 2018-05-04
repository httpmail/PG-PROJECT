#include <iostream>
#include <condition_variable>
#include "PGUtil.h"
#include <ctime>
#include <time.h>
#include <iomanip>
#include <sstream>
int main()
{
#if 1
    using namespace std::chrono;
    auto timestamp = system_clock::to_time_t(std::chrono::system_clock::now());

    std::tm t;
    localtime_s(&t, &timestamp);
    auto time = std::put_time(&t, "%F %T");

    std::stringstream str;
    str << time;
    std::cout << time << std::endl;
    std::cout << std::setw(6) <<std::setprecision(5) << std::left << std::setfill('0') << 12.32 << std::endl;
#endif
    while (1) {
        std::cout << PG::Timestamp2StrMilliseconds(PG::GetTimeStamp()) << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}