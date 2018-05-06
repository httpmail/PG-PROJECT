#include <iostream>
#include <condition_variable>
#include "PGUtil.h"
#include <ctime>
#include <time.h>
#include <iomanip>
#include <sstream>
#include "PGLog.h"

int main()
{
    PG::Log::Instance().Initilize();
    while (1) {
        LOG_INFO("abc", "xxxxxxxxxxxx");
        LOG_WARNING("abc", "yyyyyyyyyyyy");
        LOG_ERROR("abc", "zzzzzzzzzzzzzzzz");
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}