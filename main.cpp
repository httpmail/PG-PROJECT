
#include "PGLog.h"
#include <iostream>

int main()
{
    PG::Log::Instance().Initilize();

    int cout = 10;
    while (cout--)
    {
        PG_LOG_INFO("abcd", "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx %d", cout);
    }
    std::cout << "quit " << std::endl;
    return 0;
}