/**
 * @file
 * @copyright Copyright (c) 2022-2023.
 */

#include <cassert>
#include <chrono>
#include <ctime>
#include <gtest/gtest.h>
#include <iomanip>
#include <Logger.h>
#include <memory>
#include <sstream>
#include <string>

using namespace testing;
using namespace logger;

/**
 * @brief Test suite of logger.
 */
class LoggerTest
    : public Test
    , public WithParamInterface<Logger::LogLevel>
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
     * @brief Log a message.
     *
     * @param level Log level of the message.
     * @param msg Message to log.
     */
    void log(const Logger::LogLevel& level, const std::string& msg)
    {
        switch (level) {
        case Logger::LogLevel::FATAL:
            mLogger->logFatal(msg);
        case Logger::LogLevel::ERROR:
            mLogger->logError(msg);
        case Logger::LogLevel::WARNING:
            mLogger->logWarning(msg);
        case Logger::LogLevel::INFO:
            mLogger->logInfo(msg);
        case Logger::LogLevel::DEBUG:
            mLogger->logDebug(msg);
        case Logger::LogLevel::VERBOSE:
            mLogger->logVerbose(msg);
        case Logger::LogLevel::NONE:
        default:
            break;
        }
    }

    /**
     * @brief Get the log level as string.
     *
     * @param level Log level.
     *
     * @return Log level as string.
     */
    std::string getLogLevelStr(const Logger::LogLevel& level)
    {
        switch (level) {
        case Logger::LogLevel::FATAL:
            return "FATAL";
        case Logger::LogLevel::ERROR:
            return "ERROR";
        case Logger::LogLevel::WARNING:
            return "WARNING";
        case Logger::LogLevel::INFO:
            return "INFO";
        case Logger::LogLevel::DEBUG:
            return "DEBUG";
        case Logger::LogLevel::VERBOSE:
            return "VERBOSE";
        case Logger::LogLevel::NONE:
            // This level should not be logged
        default:
            return "";
        }
    }

    /**
     * @brief Get the date and time from the last logged message.
     *
     * @return Date and time.
     */
    auto getDateTime()
    {
        // Date time format in the log
        const std::string dateTime{"[YYYY-MM-DD HH:MM:SS]"};
        // Length of the substring that contains the date and time in the log
        const auto dateTimeLength = dateTime.size();
        // Index of the message string where the date and time substring begins
        constexpr auto dateTimeIndex = 0;

        return mStream.str().substr(dateTimeIndex, dateTimeLength);
    }

    /**
     * @brief Build the expected logged message, without date and time.
     *
     * @param level Log level of the message.
     * @param dateTime Expected date and time of the logged message.
     * @param msg Expected logged message.
     *
     * @return Expected logged message.
     */
    auto expectLog(const Logger::LogLevel& level, const std::string& dateTime, const std::string& msg)
    {
        std::stringstream ss;
        ss << dateTime << "[" << getLogLevelStr(level) << "] " << msg << std::endl;
        return ss.str();
    }

protected:
    /// Logger.
    std::unique_ptr<Logger> mLogger;
    //// Logger stream.
    std::ostringstream mStream{};
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
 * @brief Test the log of a message using the provided log level.
 */
TEST_P(LoggerTest, LogMessage)
{
    const auto level = GetParam();

    // Set logger level
    auto levelCopy = level;
    mLogger->setLogLevel(std::move(levelCopy));
    ASSERT_EQ(mLogger->getLogLevel(), level);

    // Log a message
    const std::string msg{"A message"};
    log(level, msg);

    // Expected message
    const std::string expectMsg{expectLog(level, getDateTime(), msg)};
    EXPECT_EQ(mStream.str(), expectMsg);
}

/**
 * @brief Test that if the logger level setted is smaller than the logged message level, the message is not logged.
 */
TEST_P(LoggerTest, DoNotLogMessage)
{
    const auto messageLevel = GetParam();
    assert(messageLevel != Logger::LogLevel::NONE);

    // Set logger level to the previous level of the message
    auto loggerLevel
        = static_cast<Logger::LogLevel>(static_cast<std::underlying_type_t<Logger::LogLevel>>(messageLevel) - 1);
    mLogger->setLogLevel(std::move(loggerLevel));

    // Log a message
    const std::string msg{"A message"};
    log(messageLevel, msg);

    // Expect no logged message
    EXPECT_TRUE(mStream.str().empty());
}

/**
 * @brief Instantiation of the logger test suite for different log levels.
 */
INSTANTIATE_TEST_SUITE_P(ParameterizedLogLevel,
                         LoggerTest,
                         Values(Logger::LogLevel::FATAL,
                                Logger::LogLevel::ERROR,
                                Logger::LogLevel::WARNING,
                                Logger::LogLevel::INFO,
                                Logger::LogLevel::DEBUG,
                                Logger::LogLevel::VERBOSE));
