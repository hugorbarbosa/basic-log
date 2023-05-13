/**
 * @file
 * @copyright Copyright (c) 2022-2023.
 */

#pragma once

#include <gmock/gmock.h>
#include <logger/Logger.h>

namespace tests {
namespace mocks {
namespace logger {

/**
 * @brief Mock of Logger.
 */
class MockLogger : public ::logger::Logger
{
public:
    /**
     * @brief Constructor.
     *
     * @param ostream Output stream.
     * @param level Log level.
     */
    explicit MockLogger(std::ostream& ostream, const LogLevel& level = cLogLevelDefault)
        : Logger(ostream, level)
    {
    }

    /// Mock method setLogLevel.
    MOCK_METHOD(void, setLogLevel, (const LogLevel&), (override));
    /// Mock method getLogLevel.
    MOCK_METHOD(LogLevel, getLogLevel, (), (const, override));
    /// Mock method logFatal.
    MOCK_METHOD(void, logFatal, (const std::string&), (override));
    /// Mock method logError.
    MOCK_METHOD(void, logError, (const std::string&), (override));
    /// Mock method logWarning.
    MOCK_METHOD(void, logWarning, (const std::string&), (override));
    /// Mock method logInfo.
    MOCK_METHOD(void, logInfo, (const std::string&), (override));
    /// Mock method logDebug.
    MOCK_METHOD(void, logDebug, (const std::string&), (override));
    /// Mock method logVerbose.
    MOCK_METHOD(void, logVerbose, (const std::string&), (override));
};

} // namespace logger
} // namespace mocks
} // namespace tests
