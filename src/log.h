#ifndef LOG_H
#define LOG_H

#include <sstream>
#include <chrono>
#include <format>
#include <thread>
#include <string_view>

enum LogLevel {
    INFO,
    DEBUG,
    WARNING,
    ERROR,
};

class Logger;

Logger getLogger(std::string prefix = "");

[[nodiscard]] constexpr std::string_view getLogLevelStr(LogLevel level) {
    switch (level) {
    case INFO:    return "INFO";
    case DEBUG:   return "DEBUG";
    case WARNING: return "WARNING";
    case ERROR:   return "ERROR";
    default:      return "UNKNOWN";
    }
}

class LogLine {
public:
    explicit LogLine(std::ostringstream&& stream);
    ~LogLine();

    LogLine(LogLine&&) = default;
    LogLine& operator=(LogLine&&) = default;
    LogLine(const LogLine&) = delete;
    LogLine& operator=(const LogLine&) = delete;

    template <typename T>
    LogLine& operator<< (const T& obj) {
        m_stream << obj;
        return *this;
    }
private:
    std::ostringstream m_stream;
};

class Logger {
public:
    explicit Logger(std::string prefix = "");

    LogLine operator() (LogLevel level);

    template <typename T>
    LogLine operator<< (const T& obj) {
        LogLine line = (*this)(INFO);
        line << obj;
        return line;
    }

private:
    std::string m_prefix;
};

#endif // LOG_H
