#include <thread>
#include <gtest/gtest.h>

#include "log/logger_interface.h"

namespace Test {
static std::string logcontent;
void handleLog(
    basic::LocalLogTime time,
    basic::LocalLogModule mod,
    basic::LocalLogLevel level,
    basic::LocalLogLocation location,
    basic::LocalLogContent content
) {
    logcontent = content;
}

class LogTest: public testing::Test {
public:
    LogTest() = default;
    ~LogTest() = default;

    void SetUp() override {
        basic::Logger::setLogHandler(handleLog);
        basic::Logger::setLevelMask(basic::kLocalLogLevelAll);
    }

    void TearDown() override {
        basic::Logger::setLogHandler(nullptr);
    }
};

TEST_F(LogTest, NormalUsed) {
    logcontent = "";
    LDebug("t") << "test debug";
    EXPECT_EQ(logcontent, "test debug");
    LInfo("t") << "test info";
    EXPECT_EQ(logcontent, "test info");
    LError("t") << "test error";
    EXPECT_EQ(logcontent, "test error");
    LWarning("t") << "test warning";
    EXPECT_EQ(logcontent, "test warning");
    LStats("t") << "test stats";
    EXPECT_EQ(logcontent, "test stats");
}

TEST_F(LogTest, OnlyDebug) {
    basic::Logger::setLevelMask(basic::LocalLogLevel::kLocalLogLevelDebug);

    logcontent = "";
    LDebug("t") << "test debug";
    EXPECT_EQ(logcontent, "test debug");
    LInfo("t") << "test info";
    EXPECT_NE(logcontent, "test info");
    LError("t") << "test error";
    EXPECT_NE(logcontent, "test error");
    LWarning("t") << "test warning";
    EXPECT_NE(logcontent, "test warning");
    LStats("t") << "test stats";
    EXPECT_NE(logcontent, "test stats");
}

TEST_F(LogTest, OnlyInfo) {
    basic::Logger::setLevelMask(basic::LocalLogLevel::kLocalLogLevelInfo);

    logcontent = "";
    LDebug("t") << "test debug";
    EXPECT_NE(logcontent, "test debug");
    LInfo("t") << "test info";
    EXPECT_EQ(logcontent, "test info");
    LError("t") << "test error";
    EXPECT_NE(logcontent, "test error");
    LWarning("t") << "test warning";
    EXPECT_NE(logcontent, "test warning");
    LStats("t") << "test stats";
    EXPECT_NE(logcontent, "test stats");
}

TEST_F(LogTest, OnlyWarning) {
    basic::Logger::setLevelMask(basic::LocalLogLevel::kLocalLogLevelWarning);

    logcontent = "";
    LDebug("t") << "test debug";
    EXPECT_NE(logcontent, "test debug");
    LInfo("t") << "test info";
    EXPECT_NE(logcontent, "test info");
    LError("t") << "test error";
    EXPECT_NE(logcontent, "test error");
    LWarning("t") << "test warning";
    EXPECT_EQ(logcontent, "test warning");
    LStats("t") << "test stats";
    EXPECT_NE(logcontent, "test stats");
}

TEST_F(LogTest, OnlyError) {
    basic::Logger::setLevelMask(basic::LocalLogLevel::kLocalLogLevelError);

    logcontent = "";
    LDebug("t") << "test debug";
    EXPECT_NE(logcontent, "test debug");
    LInfo("t") << "test info";
    EXPECT_NE(logcontent, "test info");
    LError("t") << "test error";
    EXPECT_EQ(logcontent, "test error");
    LWarning("t") << "test warning";
    EXPECT_NE(logcontent, "test warning");
    LStats("t") << "test stats";
    EXPECT_NE(logcontent, "test stats");
}

TEST_F(LogTest, OnlyStats) {
    basic::Logger::setLevelMask(basic::LocalLogLevel::kLocalLogLevelStats);

    logcontent = "";
    LDebug("t") << "test debug";
    EXPECT_NE(logcontent, "test debug");
    LInfo("t") << "test info";
    EXPECT_NE(logcontent, "test info");
    LError("t") << "test error";
    EXPECT_NE(logcontent, "test error");
    LWarning("t") << "test warning";
    EXPECT_NE(logcontent, "test warning");
    LStats("t") << "test stats";
    EXPECT_EQ(logcontent, "test stats");
}

static long long debug_times= 0;
static long long info_times = 0;
static long long warning_times = 0;
static long long error_times = 0;
static long long stats_times = 0;
void stats_Log(
    basic::LocalLogTime time,
    basic::LocalLogModule mod,
    basic::LocalLogLevel level,
    basic::LocalLogLocation location,
    basic::LocalLogContent content
) {
    switch(level) {
        case basic::LocalLogLevel::kLocalLogLevelDebug:
            debug_times++;
            break;
        case basic::LocalLogLevel::kLocalLogLevelInfo:
            info_times++;
            break;
        case basic::LocalLogLevel::kLocalLogLevelWarning:
            warning_times++;
            break;
        case basic::LocalLogLevel::kLocalLogLevelError:
            error_times++;
            break;
        case basic::LocalLogLevel::kLocalLogLevelStats:
            stats_times++;
            break;
        default:
            break;
    }
}

void repeat_report(int times) {
    for(int i=0; i<times; ++i){
        LDebug("t") << "test debug";
        LInfo("t") << "test info";
        LError("t") << "test error";
        LWarning("t") << "test warning";
        LStats("t") << "test stats";
    }
}

TEST_F(LogTest, MultiThreadedAndRepeat) {
    // check if logs will be lost
    basic::Logger::setLogHandler(stats_Log);
    for(int i=0; i<100; ++i) {
        std::thread t(repeat_report, 10000);
        t.join();
    }
    EXPECT_EQ(debug_times, 100*10000);
    EXPECT_EQ(info_times, 100*10000);
    EXPECT_EQ(warning_times, 100*10000);
    EXPECT_EQ(error_times, 100*10000);
    EXPECT_EQ(stats_times, 100*10000);
}
}