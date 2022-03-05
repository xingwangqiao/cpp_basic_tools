#include "logger.h"

namespace basic {
// implement of LogToLine function
LogToLine::~LogToLine() {
    write_line();
}

LogToLine::LogToLine(LocalLogLocation location, LocalLogModule mod, LocalLogLevel level) :
                    location_(location),
                    module_(mod),
                    level_(level),
                    time_(std::chrono::system_clock::now()) { }

LogToLine::LogToLine(LogToLine&& line) : location_(std::move(line.location_)),
                                         module_(std::move(line.module_)),
                                         time_(std::move(line.time_)),
                                         level_(std::move(line.level_)) { }

LogToLine& LogToLine::operator= (LogToLine&& line) {
    if(this == &line)
        return *this;
    location_ = std::move(line.location_);
    module_ = std::move(line.module_);
    time_ = std::move(line.time_);
    level_ = std::move(line.level_);
    return *this;
}

LogToLine& LogToLine::operator<< (LocalLogEnd end) {
    write_line();
    return *this;
}

void LogToLine::write_line() {
    // check oos_ content is null ?
    auto begin_pos = oos_.tellp();
    bool is_empty  = (oos_.seekp(0, std::ios_base::end).tellp() == 0);
    oos_.seekp(begin_pos);
    if(is_empty)
        return ;

    // trigger the write callback
    Logger::write(time_, module_, level_, location_, oos_.str());

    // reset oos_
    oos_.str() = "";    // clear content
    oos_.clear();       // clear flag
}


// implement of Logger function
Logger::Logger(LocalLogLevel level) : level_(level) { }

Logger Logger::debug(kLocalLogLevelDebug);
Logger Logger::info(kLocalLogLevelInfo);
Logger Logger::warning(kLocalLogLevelWarning);
Logger Logger::error(kLocalLogLevelError);
Logger Logger::stats(kLocalLogLevelStats);

std::mutex Logger::log_mutex_;

LocalLogHandler Logger::m_log_writer_ = nullptr;

LocalLogLevel Logger::s_level_mask_ = (LocalLogLevel)(0x0 - 1);

void Logger::setLogHandler(LocalLogHandler handler) {
    std::lock_guard<std::mutex> _(log_mutex_);
    Logger::m_log_writer_ = handler;
}

void Logger::setLevelMask(LocalLogLevel allow_levels) {
    std::lock_guard<std::mutex> _(log_mutex_);
    Logger::s_level_mask_ = allow_levels;
}

void Logger::write(LocalLogTime time,
                LocalLogModule mod,
                LocalLogLevel level,
                LocalLogLocation location,
                LocalLogContent context) {
    std::lock_guard<std::mutex> _(log_mutex_);
    if(!m_log_writer_ || !(s_level_mask_ & level))
        return ;
    m_log_writer_(time, mod, level, location, context);
}

LogToLine Logger::operator() (LocalLogLocation location, LocalLogModule mod) {
    return LogToLine(location, mod, level_);
}
}