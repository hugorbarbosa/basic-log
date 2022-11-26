/**
 * @file
 * @copyright Copyright (c) 2022.
 */

#include "Logger.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

namespace logger {

namespace {

/**
 * @brief Check if the message shall be logged, dependent of the log level defined.
 *
 * @param loggerLevel Logger level.
 * @param msgLevel Message level.
 *
 * @return True if message shall be logged.
 * @return False if message shall not be logged.
 */
bool shallLog(const Logger::LogLevel loggerLevel, const Logger::LogLevel msgLevel)
{
    if (loggerLevel >= msgLevel) {
        return true;
    }
    return false;
}

} // namespace

Logger::Logger(std::ostream& ostream, const LogLevel level)
    : mOstream{ostream}
    , mLogLevel{std::move(level)}
{
}

void Logger::setLogLevel(const LogLevel level)
{
    mLogLevel = std::move(level);
}

Logger::LogLevel Logger::getLogLevel() const
{
    return mLogLevel;
}

void Logger::logFatal(const std::string& msg)
{
    if (shallLog(mLogLevel, LogLevel::FATAL)) {
        log("FATAL", msg);
    }
}

void Logger::logError(const std::string& msg)
{
    if (shallLog(mLogLevel, LogLevel::ERROR)) {
        log("ERROR", msg);
    }
}

void Logger::logWarning(const std::string& msg)
{
    if (shallLog(mLogLevel, LogLevel::WARNING)) {
        log("WARNING", msg);
    }
}

void Logger::logInfo(const std::string& msg)
{
    if (shallLog(mLogLevel, LogLevel::INFO)) {
        log("INFO", msg);
    }
}

void Logger::logDebug(const std::string& msg)
{
    if (shallLog(mLogLevel, LogLevel::DEBUG)) {
        log("DEBUG", msg);
    }
}

void Logger::logVerbose(const std::string& msg)
{
    if (shallLog(mLogLevel, LogLevel::VERBOSE)) {
        log("VERBOSE", msg);
    }
}

void Logger::log(const std::string& level, const std::string& msg)
{
    mOstream << getDateTime() << "[" << level << "] " << msg << std::endl;
}

const std::string Logger::getDateTime() const
{
    // Current point in time
    const auto now{std::chrono::system_clock::now()};

    // Time converted to std::time_t
    const auto nowConv{std::chrono::system_clock::to_time_t(now)};

    std::stringstream ss{};
    ss << "[";
    ss << std::put_time(std::localtime(&nowConv), "%Y-%m-%d %X");
    ss << "]";

    return ss.str();
}

} // namespace logger
