#pragma once

#include <sstream>
#include <iostream>
#include <chrono>
#include <functional>
#include <mutex>

#include "code_location.h"
namespace basic {
// define log structure
using LocalLogTime = decltype(std::chrono::system_clock::now());

using LocalLogEnd = std::basic_ostream<
                        std::stringstream::char_type,
                        std::stringstream::traits_type>;

enum LocalLogLevel {
    kLocalLogLevelDebug = 1,
    kLocalLogLevelInfo = 1 << 1,
    kLocalLogLevelWarning = 1 << 2,
    kLocalLogLevelError = 1 << 3,
    kLocalLogLevelStats = 1 << 4,
    kLocalLogLevelAll = (0x0 - 1),
};

using LocalLogModule = std::string;

using LocalLogLocation = basic::CodeLocation;

using LocalLogContent = std::string;

// define callback to handle log
using LocalLogHandler = std::function<void(
    LocalLogTime,
    LocalLogModule,
    LocalLogLevel,
    LocalLogLocation,
    LocalLogContent
)>;

class LogToLine;

// define logger
class Logger {
public:
    Logger() = delete;
    ~Logger() = default;

    Logger(LocalLogLevel level);

    LogToLine operator() (LocalLogLocation location, LocalLogModule mod);

public:
    static void setLogHandler(LocalLogHandler handler);

    static void setLevelMask(LocalLogLevel allow_levels);

    static void write(LocalLogTime,
                      LocalLogModule,
                      LocalLogLevel,
                      LocalLogLocation,
                      LocalLogContent);

public:
    static Logger debug;
    static Logger info;
    static Logger warning;
    static Logger error;
    static Logger stats;

private:
    static std::mutex log_mutex_;
    static LocalLogLevel s_level_mask_;
    static LocalLogHandler m_log_writer_;

private:
    LocalLogLevel level_;
};


class LogToLine {
public:
    LogToLine() = delete;
    ~LogToLine();

    LogToLine(const LogToLine&) = delete;
    LogToLine& operator= (const LogToLine&) = delete;

    LogToLine(LogToLine&& line);
    LogToLine& operator= (LogToLine&& line);

    template<typename T>
    LogToLine& operator<< (const T& t) {
        oos_ << t;
        return *this;
    }

    template <
        typename T,
        typename std::enable_if<
            std::is_same<typename std::decay<T>::type, char>::value             || \
            std::is_same<typename std::decay<T>::type, signed char>::value      || \
            std::is_same<typename std::decay<T>::type, unsigned char>::value,
            int >::type = 0 >
    LogToLine& operator<< (T* tptr) {
        oos_ << (tptr ? tptr : "");
        return *this;
    }

    // adapted to std::endl
    LogToLine& operator<< (LocalLogEnd end);

private:
    friend Logger;
    LogToLine(LocalLogLocation location, LocalLogModule mod, LocalLogLevel level);

    void write_line();

private:

    LocalLogTime time_;
    LocalLogModule module_;
    LocalLogLevel level_;
    LocalLogLocation location_;

    std::ostringstream oos_;
};
}