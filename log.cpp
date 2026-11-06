#include "log.h"

const char* getLogLevelStr(LogLevel level) {
    switch (level)
    {
    case INFO:
        return "INFO";
    case DEBUG:
        return "DEBUG";
    case WARNING:
        return "WARNING";
    case ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

Logger getLogger(std::string prefix) {
    return Logger(prefix);
}

LogLine::~LogLine() {
    std::cout << std::endl;
}

Logger::Logger(std::string prefix)
    : m_prefix(prefix) {}

Logger Logger::operator() (LogLevel level) {
    return Logger(*this, level);
}

Logger::Logger(const Logger& logger, LogLevel log_level)
    : m_prefix(logger.m_prefix), m_log_level(log_level) {}