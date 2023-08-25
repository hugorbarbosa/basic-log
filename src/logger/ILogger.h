/**
 * @file
 * @copyright Copyright (c) 2023.
 */

#pragma once

#include <cstdint>
#include <string>

namespace logger {

/**
 * @brief Logger interface.
 */
class ILogger
{
public:
    /**
     * @brief Enumeration of the log levels.
     *
     * The log level defines the level for the logger. For example, if the log level is setted to INFO, the levels above
     * (WARNING, ERROR and FATAL) will be logged, but the levels below (DEBUG and VERBOSE) will not be logged.
     */
    enum class LogLevel : uint8_t {
        /// No messages.
        NONE = 0,
        /// Fatal message.
        FATAL = 1,
        /// Error message.
        ERROR = 2,
        /// Warning message.
        WARNING = 3,
        /// Information message.
        INFO = 4,
        /// Debug message.
        DEBUG = 5,
        /// Verbose message.
        VERBOSE = 6
    };

    /**
     * @brief Destructor.
     */
    virtual ~ILogger() = default;

    /**
     * @brief Set the log level.
     *
     * @param level Log level.
     */
    virtual void setLogLevel(LogLevel&& level) noexcept = 0;

    /**
     * @brief Get the log level.
     *
     * @return Log level.
     */
    virtual LogLevel getLogLevel() const noexcept = 0;

    /**
     * @brief Log a fatal message.
     *
     * @param msg Message to log.
     */
    virtual void logFatal(const std::string& msg) const noexcept = 0;

    /**
     * @brief Log an error message.
     *
     * @param msg Message to log.
     */
    virtual void logError(const std::string& msg) const noexcept = 0;

    /**
     * @brief Log a warning message.
     *
     * @param msg Message to log.
     */
    virtual void logWarning(const std::string& msg) const noexcept = 0;

    /**
     * @brief Log an information message.
     *
     * @param msg Message to log.
     */
    virtual void logInfo(const std::string& msg) const noexcept = 0;

    /**
     * @brief Log a debug message.
     *
     * @param msg Message to log.
     */
    virtual void logDebug(const std::string& msg) const noexcept = 0;

    /**
     * @brief Log a verbose message.
     *
     * @param msg Message to log.
     */
    virtual void logVerbose(const std::string& msg) const noexcept = 0;
};

} // namespace logger
