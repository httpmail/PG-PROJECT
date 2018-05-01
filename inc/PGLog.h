#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>

namespace PG{
    class Log {
    public:
        enum Level {
            Normal,
            Warning,
            Error,
        };

    public:
        static Log& Instance() { static Log sLog; return sLog; }

        bool Initilize(const std::string& logPath = nullptr);
        void Output(const char *pModule, const char *pFile, int line, Level eLevel, const char *pFormat, ...);
    public:
        Log(const Log&) = delete;
        Log& operator=(const Log&) = delete;

    private:
        Log();
        ~Log();

        static void WrittingThread(Log *pOwn);

    private:
        std::thread *m_pthread;
        std::mutex   m_writting_mutex;
        std::condition_variable m_writting_condition;
    };
}