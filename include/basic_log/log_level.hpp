/**
 * @file
 * @copyright Copyright (C) 2025 Hugo Barbosa.
 */

#ifndef BASIC_LOG_LOG_LEVEL_HPP
#define BASIC_LOG_LOG_LEVEL_HPP

#include <cstdint>

namespace basic_log {

/**
 * @brief Possible logging levels.
 *
 * @note The logging level is the minimum level for logging a message. For example, if the level is
 * defined to "info", the messages with the higher levels "warning", "error" and "fatal" will also
 * be logged, but the messages with lower level ("debug" and "verbose") will not be logged.
 */
enum class LogLevel : std::uint8_t {
    /// No logging.
    none,
    /// "Fatal" logging level.
    fatal,
    /// "Error" logging level.
    error,
    /// "Warning" logging level.
    warning,
    /// "Info" logging level.
    info,
    /// "Debug" logging level.
    debug,
    /// "Verbose" logging level.
    verbose
};

} // namespace basic_log

#endif // BASIC_LOG_LOG_LEVEL_HPP
