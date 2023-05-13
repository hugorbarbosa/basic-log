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
 * @return True if the message shall be logged.
 * @return False if the message shall not be logged.
 */
bool shallLog(const Logger::LogLevel& loggerLevel, const Logger::LogLevel& msgLevel)
{
    return (loggerLevel >= msgLevel) ? true : false;
}

/**
 * @brief Gets the log level as string.
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

} // namespace

Logger::Logger(std::ostream& ostream, const LogLevel& level)
    : mOstream{ostream}
    , mLogLevel{level}
{
}

void Logger::setLogLevel(const LogLevel& level)
{
    mLogLevel = level;
}

Logger::LogLevel Logger::getLogLevel() const
{
    return mLogLevel;
}

void Logger::logFatal(const std::string& msg)
{
    log(LogLevel::FATAL, msg);
}

void Logger::logError(const std::string& msg)
{
    log(LogLevel::ERROR, msg);
}

void Logger::logWarning(const std::string& msg)
{
    log(LogLevel::WARNING, msg);
}

void Logger::logInfo(const std::string& msg)
{
    log(LogLevel::INFO, msg);
}

void Logger::logDebug(const std::string& msg)
{
    log(LogLevel::DEBUG, msg);
}

void Logger::logVerbose(const std::string& msg)
{
    log(LogLevel::VERBOSE, msg);
}

void Logger::log(const LogLevel& level, const std::string& msg)
{
    if (shallLog(mLogLevel, level)) {
        mOstream << "[" << getDateTime() << "]"
                 << "[" << getLogLevelStr(level) << "] " << msg << std::endl;
    }
}

std::string Logger::getDateTime() const
{
    // Current point in time
    const auto now{std::chrono::system_clock::now()};

    // Time converted to std::time_t
    const auto nowConv{std::chrono::system_clock::to_time_t(now)};

    std::stringstream ss{};
    ss << std::put_time(std::localtime(&nowConv), "%Y-%m-%d %X");

    return ss.str();
}

} // namespace logger
