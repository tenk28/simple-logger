#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <ctime>
#include <iomanip>
#include <thread>

enum LogLevel {
    INFO,
    DEBUG,
    WARNING,
    ERROR,
};

class Logger;

const char* getLogLevelStr(LogLevel level);
Logger getLogger(std::string prefix = "");

class LogLine {
public:
    template <typename T>
    LogLine& operator<< (const T& obj) {
        std::cout << obj;
        return *this;
    }
    ~LogLine();
};

class Logger {
public:
    Logger(std::string prefix = "");

    Logger operator() (LogLevel level);

    template <typename T>
    LogLine operator<< (const T& obj) {
        // example
        // 23.02.2020 18:06:06; INFO; (1020):
        const std::time_t now = std::time(nullptr);

        std::cout << std::put_time(localtime(&now), "%d.%m.%Y %T") << "; "
            << getLogLevelStr(m_log_level) << "; "
            << m_prefix << '(' << std::this_thread::get_id() << "): "
            << obj;

        return LogLine();
    }

private:
    Logger(const Logger& logger, LogLevel log_level);

    LogLevel m_log_level = INFO;
    std::string m_prefix;
};

#endif // LOG_H
