/**
 * @file
 * @copyright Copyright (c) 2022-2023.
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
 * @return True if the message shall be logged, false otherwise.
 */
bool shallLog(const Logger::LogLevel& loggerLevel, const Logger::LogLevel& msgLevel)
{
    return loggerLevel >= msgLevel;
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
 * @brief Get the current date and time.
 *
 * Format of the output: YYYY-MM-DD HH:MM:SS.
 *
 * @return String with the current date and time.
 */
std::string getDateTime()
{
    // Current point in time
    const auto now = std::chrono::system_clock::now();

    // Time converted to std::time_t
    const auto nowConv = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss{};
    ss << std::put_time(std::localtime(&nowConv), "%Y-%m-%d %X");

    return ss.str();
}

} // namespace

Logger::Logger(std::ostream& ostream, const LogLevel& level)
    : mOstream{ostream}
    , mLogLevel{level}
{
}

void Logger::setLogLevel(LogLevel&& level) noexcept
{
    mLogLevel = std::move(level);
}

Logger::LogLevel Logger::getLogLevel() const noexcept
{
    return mLogLevel;
}

void Logger::logFatal(const std::string& msg) const noexcept
{
    log(LogLevel::FATAL, msg);
}

void Logger::logError(const std::string& msg) const noexcept
{
    log(LogLevel::ERROR, msg);
}

void Logger::logWarning(const std::string& msg) const noexcept
{
    log(LogLevel::WARNING, msg);
}

void Logger::logInfo(const std::string& msg) const noexcept
{
    log(LogLevel::INFO, msg);
}

void Logger::logDebug(const std::string& msg) const noexcept
{
    log(LogLevel::DEBUG, msg);
}

void Logger::logVerbose(const std::string& msg) const noexcept
{
    log(LogLevel::VERBOSE, msg);
}

void Logger::log(const LogLevel& level, const std::string& msg) const
{
    if (shallLog(mLogLevel, level)) {
        mOstream << "[" << getDateTime() << "]"
                 << "[" << getLogLevelStr(level) << "] " << msg << std::endl;
    }
}

} // namespace logger
