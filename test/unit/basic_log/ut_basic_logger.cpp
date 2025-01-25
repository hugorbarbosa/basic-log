/**
 * @file
 * @copyright Copyright (C) 2025 Hugo Barbosa.
 */

#include <basic_log/basic_logger.h>
#include <basic_log_utils.h>
#include <gtest/gtest.h>

using namespace testing;
using namespace basic_log;

/**
 * @brief Unit testing of basic logger.
 */
class UtBasicLogger : public Test {
protected:
    /**
     * @brief Constructor.
     */
    UtBasicLogger() noexcept
        : basic_logger{stream}
    {
    }

    /**
     * @brief Log a message.
     *
     * @param level Logging level of the message.
     * @param msg Message to log.
     */
    void log(const LogLevel level, const std::string& msg) noexcept
    {
        switch (level) {
        case LogLevel::fatal:
            basic_logger.fatal(msg);
        case LogLevel::error:
            basic_logger.error(msg);
        case LogLevel::warning:
            basic_logger.warning(msg);
        case LogLevel::info:
            basic_logger.info(msg);
        case LogLevel::debug:
            basic_logger.debug(msg);
        case LogLevel::verbose:
            basic_logger.verbose(msg);
        case LogLevel::none:
        default:
            break;
        }
    }

    /**
     * @brief Extract the date and time from the last logged message.
     *
     * @return Date and time.
     */
    auto extract_date_time() const noexcept
    {
        const auto date_time = get_date_time();
        const auto size = date_time.size();
        constexpr auto substring_index = 4;
        return stream.str().substr(substring_index, size);
    }

    /**
     * @brief Get the expected logged message.
     *
     * @param msg Expected message.
     * @param level Expected logging level of the message.
     * @param index Expected index of the message.
     * @param date_time Expected date and time of the message.
     * @param thread_id Expected thread ID of the message.
     *
     * @return Expected logged message.
     */
    auto get_expected_log(const std::string& msg,
                          const LogLevel level,
                          const std::uint16_t index,
                          const std::string& date_time,
                          const std::thread::id& thread_id) const noexcept
    {
        std::stringstream ss;
        ss << "[" << index << "]"
           << "[" << date_time << "]"
           << "[" << get_log_level_str(level) << "]"
           << "[T" << thread_id << "] " << msg << std::endl;
        return ss;
    }

    /// Basic logger under testing.
    BasicLogger basic_logger;
    //// Logger stream.
    std::ostringstream stream;
};

/**
 * @brief Parameterized test fixture for testing different logging levels.
 */
class ParamTestBasicLogger
    : public UtBasicLogger
    , public WithParamInterface<LogLevel> {
};

/**
 * @brief Instantiation of the parameterized test fixture.
 */
INSTANTIATE_TEST_SUITE_P(LoggingLevel,
                         ParamTestBasicLogger,
                         Values(LogLevel::fatal,
                                LogLevel::error,
                                LogLevel::warning,
                                LogLevel::info,
                                LogLevel::debug,
                                LogLevel::verbose));

/**
 * @brief Test that the default logging level is correctly defined.
 */
TEST_F(UtBasicLogger, DefaultLogLevelIsDefined)
{
    EXPECT_EQ(basic_logger.get_log_level(), BasicLogger::default_log_level);
}

/**
 * @brief Test that the logging level is correctly defined.
 */
TEST_P(ParamTestBasicLogger, LogLevelIsSet)
{
    const auto log_level = GetParam();
    basic_logger.set_log_level(log_level);
    EXPECT_EQ(basic_logger.get_log_level(), log_level);
}

/**
 * @brief Test that a message is logged with the correct format.
 */
TEST_P(ParamTestBasicLogger, LoggedMessageHasCorrectFormat)
{
    const auto log_level = GetParam();

    basic_logger.set_log_level(log_level);

    constexpr auto msg = "A message";
    log(log_level, msg);

    constexpr auto message_index = 1;
    const auto& thread_id = std::this_thread::get_id();
    const auto expected_message
        = get_expected_log(msg, log_level, message_index, extract_date_time(), thread_id);
    EXPECT_EQ(stream.str(), expected_message.str());
}

/**
 * @brief Test that if the message level is not included in the logging level defined, the message
 * is not logged.
 */
TEST_P(ParamTestBasicLogger, MessageIsNotLoggedDueToLogLevel)
{
    const auto message_level = GetParam();
    ASSERT_NE(message_level, LogLevel::none);

    const auto previous_level
        = static_cast<LogLevel>(static_cast<std::underlying_type_t<LogLevel>>(message_level) - 1);
    basic_logger.set_log_level(previous_level);

    constexpr auto msg = "A message";
    log(message_level, msg);

    // No message should be logged.
    EXPECT_TRUE(stream.str().empty());
}

/**
 * @brief Test that the message index is incremented when multiple messages are logged.
 */
TEST_P(ParamTestBasicLogger, MessageIndexIsIncremented)
{
    const auto log_level = GetParam();

    basic_logger.set_log_level(log_level);

    constexpr auto clear_stream = [](auto& stream) {
        // Reset the internal string.
        stream.str("");
        // Clear any error flag.
        stream.clear();
    };

    const auto& thread_id = std::this_thread::get_id();
    std::uint8_t expected_index{1};
    const std::map<decltype(expected_index), std::string> messages{{expected_index, "Message 1"},
                                                                   {++expected_index, "Message 2"},
                                                                   {++expected_index, "Message 3"},
                                                                   {++expected_index, "Message 4"}};
    for (const auto& message_pair : messages) {
        const auto& msg = message_pair.second;
        clear_stream(stream);
        log(log_level, msg);

        const auto expected_message
            = get_expected_log(msg, log_level, message_pair.first, extract_date_time(), thread_id);
        EXPECT_EQ(stream.str(), expected_message.str());
    }
}
