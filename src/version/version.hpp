/**
 * @file
 * @copyright Copyright (C) 2025 Hugo Barbosa.
 */

#ifndef BASIC_LOG_VERSION_HPP
#define BASIC_LOG_VERSION_HPP

#include <string>

namespace basic_log {

/// Major version.
inline constexpr auto project_version_major = 1;
/// Minor version.
inline constexpr auto project_version_minor = 0;
/// Patch version.
inline constexpr auto project_version_patch = 0;
/// Optional prerelease version (set as "" if not needed).
inline constexpr std::string_view project_version_prerelease = "";

} // namespace basic_log

#endif // BASIC_LOG_VERSION_HPP
