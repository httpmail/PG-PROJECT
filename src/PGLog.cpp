
#include "PGLog.h"

#include "PGThread.h"
#include "PGUtil.h"

#include <thread>

#include <memory>
#include <stdarg.h>
#include <assert.h>

#include <iostream>

namespace {
    const char* GetLevelName(PG::Log::Level level)
    {
        switch (level)
        {
        case PG::Log::Level::Error:
            return "Error";

        case PG::Log::Level::Info:
            return "Info";

        case PG::Log::Level::Warning:
            return "Warning";

        default:
            return "unknow";
        }
    }
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
        static const int max_log_bytes(1024);
        static const int max_head_bytes(256);

        char log[1024];

        std::string file(pFile);
        auto pos = file.find_last_of('\\');
        if (std::string::npos == pos)
        {
            pos = file.find_first_of('/');
        }

        auto head_len = sprintf_s(log, max_head_bytes, "%s: %s %s %s [%d] :",
            GetLevelName(eLevel),
            Timestamp2StrMilliseconds(GetTimeStamp()).c_str(),
            pModule ? pModule : "UnRegisterred Module",
            file.substr(pos + 1).c_str(), 
            line);

        va_list argp;
        va_start(argp, pFormat);
        vsnprintf(&log[head_len], max_log_bytes - head_len, pFormat, argp);
        va_end(argp);

        MutexLockGuard lock(m_writting_mutex);
        m_logs.push_back(log);
        m_writting_condition.notify_one();
    }

    void Log::WrittingThread(Log *pOwn)
    {
        assert(pOwn);

        ConditionLock quit_lock(pOwn->m_quit_mutex);
        while (!pOwn->m_quit_condition.wait_for(quit_lock, std::chrono::milliseconds(0), [&pOwn] {return pOwn->m_quit; }))
        {
            ConditionLock  writting_lock(pOwn->m_writting_mutex);
            if (pOwn->m_writting_condition.wait_for(writting_lock, std::chrono::seconds(1), [&pOwn] { return !pOwn->m_logs.empty(); }))
            {
                assert(pOwn->m_logs.size());
                LogContainer logs(pOwn->m_logs.begin(), pOwn->m_logs.end());
                writting_lock.unlock();

                for (auto log : logs)
                    std::cout << log << std::endl;
            }
        }
    }
}