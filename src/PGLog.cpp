#include "PGLog.h"
#include "PGThread.h"
#include "PGUtil.h"

#include <memory>
#include <stdarg.h>
#include <assert.h>

namespace{

}
namespace PG{
    bool Log::Initilize(const std::string& logPath /*= nullptr*/)
    {
        m_pthread = new std::thread(&Log::WrittingThread, this);
        if (!m_pthread)
            return false;

        return true;
    }

    void Log::Output(const char *pModule, const char *pFile, int line, Level eLevel, const char *pFormat, ...)
    {
        assert(pFormat && pFile);

        va_list argp;
        va_start(argp, pFormat);

        char info[512];
        vsnprintf_s(info, sizeof(info), pFormat, argp);
        va_end(argp);

        char header[512];

        std::string file(pFile);
        auto pos = file.find_last_of('\\');
        if (std::string::npos == pos)
        {
            pos = file.find_first_of('/');
        }

        sprintf_s(header, sizeof(header), 
            "%lld %s %s [%d] :", 
            GetMilliTimeStamp(), 
            pModule ? pModule : "UnRegisterred Module", 
            file.substr(pos + 1).c_str(), 
            line);

        MutexLockGuard lock(m_writting_mutex);
    }

    void Log::WrittingThread(Log *pOwn)
    {
        assert(pOwn);
    }
}