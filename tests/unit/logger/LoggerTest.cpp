/**
 * @file
 * @copyright Copyright (c) 2022.
 */

#include <chrono>
#include <ctime>
#include <gtest/gtest.h>
#include <iomanip>
#include <logger/Logger.h>
#include <memory>
#include <sstream>
#include <string>

using namespace testing;
using namespace logger;

/**
 * @brief Test class of Logger.
 */
class LoggerTest : public Test
{
protected:
    /**
     * @brief Constructor.
     */
    LoggerTest()
        : mLogger{std::make_unique<Logger>(mStream)}
    {
    }

    /**
     * @brief Test suite setup.
     */
    void SetUp() override {}

    /**
     * @brief Test suite teardown.
     */
    void TearDown() override {}

    /**
     * @brief Builds the expected log, without date and time.
     *
     * @param level Log level of the message.
     * @param msg Message to log.
     *
     * @return Expected log message.
     */
    const std::string expectLog(const std::string& level, const std::string& msg)
    {
        std::stringstream ss;
        ss << "[" << level << "] " << msg << std::endl;
        return ss.str();
    }

protected:
    /// Logger.
    std::unique_ptr<Logger> mLogger;
    //// Logger stream.
    std::ostringstream mStream{};

    /// Length of the substring that contains the date and time in the log.
    static constexpr auto cDateTimeLength{21};
};

/**
 * @brief Test the log level setted.
 */
TEST_F(LoggerTest, SetLogLevel)
{
    mLogger->setLogLevel(Logger::LogLevel::NONE);
    EXPECT_EQ(mLogger->getLogLevel(), Logger::LogLevel::NONE);
}

/**
 * @brief Test the log for fatal messages.
 */
TEST_F(LoggerTest, LogFatal)
{
    mLogger->setLogLevel(Logger::LogLevel::FATAL);

    const std::string msg{"A fatal message"};
    mLogger->logFatal(msg);

    // Expected message
    const std::string dateTime{mStream.str().substr(0, cDateTimeLength)};
    const std::string expectMsg{dateTime + expectLog("FATAL", msg)};
    EXPECT_EQ(mStream.str(), expectMsg);
}

/**
 * @brief Test that if the log level setted is smaller than the fatal level, the message is not logged.
 */
TEST_F(LoggerTest, NoLogFatal)
{
    mLogger->setLogLevel(Logger::LogLevel::NONE);

    const std::string msg{"A fatal message"};
    mLogger->logFatal(msg);

    EXPECT_TRUE(mStream.str().empty());
}

/**
 * @brief Test the log for error messages.
 */
TEST_F(LoggerTest, LogError)
{
    mLogger->setLogLevel(Logger::LogLevel::ERROR);

    const std::string msg{"An error message"};
    mLogger->logError(msg);

    // Expected message
    const std::string dateTime{mStream.str().substr(0, cDateTimeLength)};
    const std::string expectMsg{dateTime + expectLog("ERROR", msg)};
    EXPECT_EQ(mStream.str(), expectMsg);
}

/**
 * @brief Test that if the log level setted is smaller than the error level, the message is not logged.
 */
TEST_F(LoggerTest, NoLogError)
{
    mLogger->setLogLevel(Logger::LogLevel::NONE);

    const std::string msg{"An error message"};
    mLogger->logError(msg);

    EXPECT_TRUE(mStream.str().empty());
}

/**
 * @brief Test the log for warning messages.
 */
TEST_F(LoggerTest, LogWarning)
{
    mLogger->setLogLevel(Logger::LogLevel::WARNING);

    const std::string msg{"A warning message"};
    mLogger->logWarning(msg);

    // Expected message
    const std::string dateTime{mStream.str().substr(0, cDateTimeLength)};
    const std::string expectMsg{dateTime + expectLog("WARNING", msg)};
    EXPECT_EQ(mStream.str(), expectMsg);
}

/**
 * @brief Test that if the log level setted is smaller than the warning level, the message is not logged.
 */
TEST_F(LoggerTest, NoLogWarning)
{
    mLogger->setLogLevel(Logger::LogLevel::NONE);

    const std::string msg{"A warning message"};
    mLogger->logWarning(msg);

    EXPECT_TRUE(mStream.str().empty());
}

/**
 * @brief Test the log for information messages.
 */
TEST_F(LoggerTest, LogInfo)
{
    mLogger->setLogLevel(Logger::LogLevel::INFO);

    const std::string msg{"An information message"};
    mLogger->logInfo(msg);

    // Expected message
    const std::string dateTime{mStream.str().substr(0, cDateTimeLength)};
    const std::string expectMsg{dateTime + expectLog("INFO", msg)};
    EXPECT_EQ(mStream.str(), expectMsg);
}

/**
 * @brief Test that if the log level setted is smaller than the information level, the message is not logged.
 */
TEST_F(LoggerTest, NoLogInfo)
{
    mLogger->setLogLevel(Logger::LogLevel::NONE);

    const std::string msg{"An information message"};
    mLogger->logInfo(msg);

    EXPECT_TRUE(mStream.str().empty());
}

/**
 * @brief Test the log for debug messages.
 */
TEST_F(LoggerTest, LogDebug)
{
    mLogger->setLogLevel(Logger::LogLevel::DEBUG);

    const std::string msg{"A debug message"};
    mLogger->logDebug(msg);

    // Expected message
    const std::string dateTime{mStream.str().substr(0, cDateTimeLength)};
    const std::string expectMsg{dateTime + expectLog("DEBUG", msg)};
    EXPECT_EQ(mStream.str(), expectMsg);
}

/**
 * @brief Test that if the log level setted is smaller than the debug level, the message is not logged.
 */
TEST_F(LoggerTest, NoLogDebug)
{
    mLogger->setLogLevel(Logger::LogLevel::NONE);

    const std::string msg{"A debug message"};
    mLogger->logDebug(msg);

    EXPECT_TRUE(mStream.str().empty());
}

/**
 * @brief Test the log for verbose messages.
 */
TEST_F(LoggerTest, LogVerbose)
{
    mLogger->setLogLevel(Logger::LogLevel::VERBOSE);

    const std::string msg{"A verbose message"};
    mLogger->logVerbose(msg);

    // Expected message
    const std::string dateTime{mStream.str().substr(0, cDateTimeLength)};
    const std::string expectMsg{dateTime + expectLog("VERBOSE", msg)};
    EXPECT_EQ(mStream.str(), expectMsg);
}

/**
 * @brief Test that if the log level setted is smaller than the verbose level, the message is not logged.
 */
TEST_F(LoggerTest, NoLogVerbose)
{
    mLogger->setLogLevel(Logger::LogLevel::NONE);

    const std::string msg{"A verbose message"};
    mLogger->logVerbose(msg);

    EXPECT_TRUE(mStream.str().empty());
}
