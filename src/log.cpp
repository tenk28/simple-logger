#include "log.h"

#include <iostream>
#include <syncstream>

Logger getLogger(std::string prefix) {
    return Logger{std::move(prefix)};
}

LogLine::LogLine(std::ostringstream&& stream)
    : m_stream{std::move(stream)} {}

LogLine::~LogLine() {
    m_stream << '\n';
    std::osyncstream{std::cout} << m_stream.str();
}

Logger::Logger(std::string prefix)
    : m_prefix{std::move(prefix)} {}

LogLine Logger::operator() (LogLevel level) {
    // example
    // 23.02.2020 18:06:06; INFO; (1020):
    const auto now = std::chrono::zoned_time{
        std::chrono::current_zone(),
        std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now())
    };

    std::ostringstream stream;
    stream << std::format("{:%d.%m.%Y %T}", now) << "; "
        << getLogLevelStr(level) << "; "
        << m_prefix << '(' << std::this_thread::get_id() << "): ";

return LogLine{std::move(stream)};
}
