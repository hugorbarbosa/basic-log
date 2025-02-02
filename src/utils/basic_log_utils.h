/**
 * @file
 * @copyright Copyright (C) 2025 Hugo Barbosa.
 */

#ifndef BASIC_LOG_UTILS_H
#define BASIC_LOG_UTILS_H

#include <basic_log/log_level.h>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <string_view>

namespace basic_log {

/**
 * @brief Get the logging level as string.
 *
 * @param level Logging level.
 *
 * @return Logging level as string.
 */
inline constexpr std::string_view get_log_level_str(const LogLevel level) noexcept
{
    switch (level) {
    case LogLevel::fatal:
        return "fatal";
    case LogLevel::error:
        return "error";
    case LogLevel::warning:
        return "warning";
    case LogLevel::info:
        return "info";
    case LogLevel::debug:
        return "debug";
    case LogLevel::verbose:
        return "verbose";
    case LogLevel::none:
    default:
        return "";
    }
}

/**
 * @brief Get the current date and time, with the format "YYYY-MM-DD HH:MM:SS.MMM".
 *
 * @return Current date and time.
 */
inline std::string get_date_time() noexcept
{
    using namespace std::chrono;
    const auto now = current_zone()->to_local(system_clock::now());

    // Get a local time_point with days precision.
    const auto ld = floor<days>(now);

    // Convert local days precision time_point to a local {y, m, d} calendar.
    const year_month_day ymd{ld};

    // Split time since local midnight into {h, m, s, subseconds}.
    const hh_mm_ss hms{now - ld};
    const auto ms = duration_cast<milliseconds>(now.time_since_epoch()).count() % 1000;

    // Format the date and time.
    std::stringstream ss;
    ss << std::setw(4) << std::setfill('0') << static_cast<int>(ymd.year()) << '-' << std::setw(2)
       << std::setfill('0') << static_cast<unsigned>(ymd.month()) << '-' << std::setw(2)
       << std::setfill('0') << static_cast<unsigned>(ymd.day()) << ' ' << std::setw(2)
       << std::setfill('0') << static_cast<int>(hms.hours().count()) << ':' << std::setw(2)
       << std::setfill('0') << static_cast<int>(hms.minutes().count()) << ':' << std::setw(2)
       << std::setfill('0') << static_cast<int>(hms.seconds().count()) << '.' << std::setw(3)
       << std::setfill('0') << ms;

    return ss.str();
}

} // namespace basic_log

#endif // BASIC_LOG_UTILS_H
