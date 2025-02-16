/**
 * @file
 * @copyright Copyright (C) 2025 Hugo Barbosa.
 */

#ifndef BASIC_LOG_BASIC_LOGGER_HPP
#define BASIC_LOG_BASIC_LOGGER_HPP

#include <atomic>
#include <mutex>
#include <string>
#include "log_level.hpp"

namespace basic_log {

/**
 * @brief Basic logger.
 */
class BasicLogger {
public:
    /// Default logging level.
    static constexpr LogLevel default_log_level{LogLevel::verbose};

    /**
     * @brief Constructor.
     *
     * @param ostream Output stream to use for message logging.
     * @param level Logging level.
     */
    explicit BasicLogger(std::ostream& ostream, const LogLevel level = default_log_level) noexcept;

    /**
     * @brief Set the logging level.
     *
     * @param level Logging level.
     */
    void set_log_level(const LogLevel level) noexcept;

    /**
     * @brief Get the logging level currently defined.
     *
     * @return Logging level.
     */
    LogLevel get_log_level() const noexcept;

    /**
     * @brief Log fatal message.
     *
     * @param msg Message to log.
     */
    void fatal(const std::string& msg) noexcept;

    /**
     * @brief Log error message.
     *
     * @param msg Message to log.
     */
    void error(const std::string& msg) noexcept;

    /**
     * @brief Log warning message.
     *
     * @param msg Message to log.
     */
    void warning(const std::string& msg) noexcept;

    /**
     * @brief Log info message.
     *
     * @param msg Message to log.
     */
    void info(const std::string& msg) noexcept;

    /**
     * @brief Log debug message.
     *
     * @param msg Message to log.
     */
    void debug(const std::string& msg) noexcept;

    /**
     * @brief Log verbose message.
     *
     * @param msg Message to log.
     */
    void verbose(const std::string& msg) noexcept;

private:
    /**
     * @brief Log a message.
     *
     * @param level Logging level of the message.
     * @param msg Message to log.
     */
    void log(const LogLevel level, const std::string& msg) noexcept;

    /**
     * @brief Check if the message should be logged, dependent of the current logging level defined.
     *
     * @param msg_level Message level to check.
     *
     * @return True if the message should be logged, false otherwise.
     */
    bool should_log(const LogLevel msg_level) const noexcept;

    /// Output stream.
    std::ostream& out_stream;
    /// Logging level.
    std::atomic<LogLevel> log_level;
    /// Mutex to protect access to the stream.
    std::mutex stream_mutex;
    /// Message index.
    std::uint64_t message_index{0};
};

} // namespace basic_log

#endif // BASIC_LOG_BASIC_LOGGER_HPP
