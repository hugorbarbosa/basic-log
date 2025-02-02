/**
 * @file
 * @copyright Copyright (C) 2025 Hugo Barbosa.
 */

#include <basic_log/basic_logger.h>
#include <basic_log_utils.h>
#include <thread>

namespace basic_log {

BasicLogger::BasicLogger(std::ostream& ostream, const LogLevel level) noexcept
    : out_stream{ostream}
    , log_level{level}
{
}

void BasicLogger::set_log_level(const LogLevel level) noexcept
{
    log_level = level;
}

LogLevel BasicLogger::get_log_level() const noexcept
{
    return log_level;
}

void BasicLogger::fatal(const std::string& msg) noexcept
{
    log(LogLevel::fatal, msg);
}

void BasicLogger::error(const std::string& msg) noexcept
{
    log(LogLevel::error, msg);
}

void BasicLogger::warning(const std::string& msg) noexcept
{
    log(LogLevel::warning, msg);
}

void BasicLogger::info(const std::string& msg) noexcept
{
    log(LogLevel::info, msg);
}

void BasicLogger::debug(const std::string& msg) noexcept
{
    log(LogLevel::debug, msg);
}

void BasicLogger::verbose(const std::string& msg) noexcept
{
    log(LogLevel::verbose, msg);
}

void BasicLogger::log(const LogLevel level, const std::string& msg) noexcept
{
    if (should_log(level)) {
        const std::lock_guard<std::mutex> lock(stream_mutex);
        out_stream << "[" << ++message_index << "]"
                   << "[" << get_date_time() << "]"
                   << "[" << get_log_level_str(level) << "]"
                   << "[T" << std::this_thread::get_id() << "] " << msg << std::endl;
    }
}

bool BasicLogger::should_log(const LogLevel msg_level) const noexcept
{
    return log_level >= msg_level;
}

} // namespace basic_log
