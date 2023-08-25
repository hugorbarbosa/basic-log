/**
 * @file
 * @copyright Copyright (c) 2022-2023.
 */

#pragma once

#include <gmock/gmock.h>
#include <ILogger.h>

namespace tests {
namespace mocks {
namespace logger {

/**
 * @brief Mock of Logger.
 */
class MockLogger : public ::logger::ILogger
{
public:
    /// Mock method setLogLevel.
    MOCK_METHOD(void, setLogLevel, (LogLevel &&), (noexcept, override));
    /// Mock method getLogLevel.
    MOCK_METHOD(LogLevel, getLogLevel, (), (const, noexcept, override));
    /// Mock method logFatal.
    MOCK_METHOD(void, logFatal, (const std::string&), (const, noexcept, override));
    /// Mock method logError.
    MOCK_METHOD(void, logError, (const std::string&), (const, noexcept, override));
    /// Mock method logWarning.
    MOCK_METHOD(void, logWarning, (const std::string&), (const, noexcept, override));
    /// Mock method logInfo.
    MOCK_METHOD(void, logInfo, (const std::string&), (const, noexcept, override));
    /// Mock method logDebug.
    MOCK_METHOD(void, logDebug, (const std::string&), (const, noexcept, override));
    /// Mock method logVerbose.
    MOCK_METHOD(void, logVerbose, (const std::string&), (const, noexcept, override));
};

} // namespace logger
} // namespace mocks
} // namespace tests
