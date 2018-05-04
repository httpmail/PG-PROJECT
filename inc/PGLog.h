#pragma once


#include <mutex>
#include <condition_variable>

#include <string>
#include <vector>

class std::thread;

namespace PG{
    class Log {
    public:
        enum class Level {
            Info,
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
        using LogContainer = std::vector<std::string>;

    private:
        bool m_quit;
        LogContainer m_logs;

        std::thread *m_pthread;
 
        std::condition_variable    m_writting_condition;
        std::mutex                          m_writting_mutex;

        std::condition_variable    m_quit_condition;
        std::mutex                          m_quit_mutex;
    };
}