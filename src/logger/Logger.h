/**
 * @file
 * @copyright Copyright (c) 2022-2023.
 */

#pragma once

#include <cstdint>
#include <ostream>

namespace logger {

/**
 * @brief Simple logger.
 */
class Logger
{
public:
    /**
     * @brief Enumeration of the log levels.
     *
     * The log level defines the level for the logger. For example, if the log level is setted to INFO, the levels above
     * (WARNING, ERROR and FATAL) will be logged, but the levels below (DEBUG and VERBOSE) will not.
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

    /// Default log level.
    static constexpr auto cLogLevelDefault{LogLevel::NONE};

    /**
     * @brief Constructor.
     *
     * @param ostream Output stream.
     * @param level Log level.
     */
    explicit Logger(std::ostream& ostream, const LogLevel& level = cLogLevelDefault);

    /**
     * @brief Destructor.
     */
    virtual ~Logger() = default;

    /**
     * @brief Set the log level.
     *
     * @param level Log level.
     */
    virtual void setLogLevel(const LogLevel& level);

    /**
     * @brief Get the log level.
     *
     * @return Log level.
     */
    [[nodiscard]] virtual LogLevel getLogLevel() const;

    /**
     * @brief Log a fatal message.
     *
     * @param msg Message to log.
     */
    virtual void logFatal(const std::string& msg);

    /**
     * @brief Log an error message.
     *
     * @param msg Message to log.
     */
    virtual void logError(const std::string& msg);

    /**
     * @brief Log a warning message.
     *
     * @param msg Message to log.
     */
    virtual void logWarning(const std::string& msg);

    /**
     * @brief Log an information message.
     *
     * @param msg Message to log.
     */
    virtual void logInfo(const std::string& msg);

    /**
     * @brief Log a debug message.
     *
     * @param msg Message to log.
     */
    virtual void logDebug(const std::string& msg);

    /**
     * @brief Log a verbose message.
     *
     * @param msg Message to log.
     */
    virtual void logVerbose(const std::string& msg);

private:
    /**
     * @brief Log a message.
     *
     * @param level Log level of the message.
     * @param msg Message to log.
     */
    void log(const LogLevel& level, const std::string& msg);

    /**
     * @brief Get the current date and time.
     *
     * Format of the output: YYYY-MM-DD HH:MM:SS.
     *
     * @return String with the current date and time.
     */
    std::string getDateTime() const;

private:
    /// Output stream.
    std::ostream& mOstream;
    /// Log level.
    LogLevel mLogLevel;
};

} // namespace logger
