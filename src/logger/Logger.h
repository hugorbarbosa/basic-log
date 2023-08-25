/**
 * @file
 * @copyright Copyright (c) 2022-2023.
 */

#pragma once

#include "ILogger.h"
#include <ostream>

namespace logger {

/**
 * @brief Simple logger.
 */
class Logger : public ILogger
{
public:
    /// Default log level.
    static constexpr LogLevel cLogLevelDefault{LogLevel::NONE};

    /**
     * @brief Constructor.
     *
     * @param ostream Output stream.
     * @param level Log level.
     */
    explicit Logger(std::ostream& ostream, const LogLevel& level = cLogLevelDefault);

    /**
     * @copydoc ILogger::setLogLevel
     */
    void setLogLevel(LogLevel&& level) noexcept override;

    /**
     * @copydoc ILogger::getLogLevel
     */
    LogLevel getLogLevel() const noexcept override;

    /**
     * @copydoc ILogger::logFatal
     */
    void logFatal(const std::string& msg) const noexcept override;

    /**
     * @copydoc ILogger::logError
     */
    void logError(const std::string& msg) const noexcept override;

    /**
     * @copydoc ILogger::logWarning
     */
    void logWarning(const std::string& msg) const noexcept override;

    /**
     * @copydoc ILogger::logInfo
     */
    void logInfo(const std::string& msg) const noexcept override;

    /**
     * @copydoc ILogger::logDebug
     */
    void logDebug(const std::string& msg) const noexcept override;

    /**
     * @copydoc ILogger::logVerbose
     */
    void logVerbose(const std::string& msg) const noexcept override;

private:
    /**
     * @brief Log a message.
     *
     * @param level Log level of the message.
     * @param msg Message to log.
     */
    void log(const LogLevel& level, const std::string& msg) const;

private:
    /// Output stream.
    std::ostream& mOstream;
    /// Log level.
    LogLevel mLogLevel;
};

} // namespace logger
