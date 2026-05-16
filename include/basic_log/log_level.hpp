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
 */
enum class LogLevel : std::uint8_t {
    /// No logging (all logging calls are ignored).
    none,
    /// Level to log fatal messages only.
    fatal,
    /// Level to log error and higher-severity messages.
    error,
    /// Level to log warnings and higher-severity messages.
    warning,
    /// Level to log informational and higher-severity messages.
    info,
    /// Level to log debug and higher-severity messages.
    debug,
    /// Level to log all messages, including verbose diagnostics.
    verbose
};

} // namespace basic_log

#endif // BASIC_LOG_LOG_LEVEL_HPP
