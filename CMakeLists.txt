#
# Copyright (C) 2025 Hugo Barbosa.
#

# ----------------------------------------------------------------------------
# Project setup
# ----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.21)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
include(ProjectVersion)
set(VERSION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/version/version.hpp)
parse_project_version(${VERSION_FILE})

project(basic_log
    VERSION ${PROJECT_VERSION_BASE}
    LANGUAGES CXX
    DESCRIPTION "Basic logging library."
)

set(BASICLOG_PROJECT_NAME ${PROJECT_NAME})
set(BASICLOG_PROJECT_VERSION ${PROJECT_VERSION_FULL})

set(MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MAIN_PROJECT ON)
endif()

# ----------------------------------------------------------------------------
# Pre-requirements
# ----------------------------------------------------------------------------
include(SourceBuilds)
validate_build_directory()

# ----------------------------------------------------------------------------
# Configuration options
# ----------------------------------------------------------------------------
option(BASICLOG_BUILD_TESTS "Build tests" ${MAIN_PROJECT})
option(BASICLOG_BUILD_EXAMPLES "Build examples" ${MAIN_PROJECT})
option(BASICLOG_ENABLE_COVERAGE "Enable code coverage analysis" OFF)
option(BASICLOG_ENABLE_CLANG_FORMAT "Enable code formatting check with clang-format" OFF)
option(BASICLOG_ENABLE_CLANG_TIDY "Enable code static analysis with clang-tidy" OFF)
option(BASICLOG_ENABLE_ASAN "Enable Address Sanitizer" OFF)
option(BASICLOG_ENABLE_LSAN "Enable Leak Sanitizer" OFF)
option(BASICLOG_ENABLE_TSAN "Enable Thread Sanitizer" OFF)
option(BASICLOG_ENABLE_UBSAN "Enable Undefined Behavior Sanitizer" OFF)
option(BASICLOG_ENABLE_DOXYGEN "Enable doxygen documentation generation" OFF)

if(BASICLOG_ENABLE_COVERAGE)
    set(BASICLOG_BUILD_TESTS ON)
endif()

# ----------------------------------------------------------------------------
# CMake options
# ----------------------------------------------------------------------------
if(MAIN_PROJECT)
    # Build type on single-configuration generators (e.g. Makefile or Ninja).
    # Set default build type if build type not set.
    if(NOT CMAKE_BUILD_TYPE)
        set(DEFAULT_BUILD_TYPE Debug)
        message(STATUS "No build type specified, setting it to '${DEFAULT_BUILD_TYPE}'")
        set(CMAKE_BUILD_TYPE ${DEFAULT_BUILD_TYPE})
    endif()

    # Generates a JSON file containing the exact compiler commands. Useful for clang-based tools.
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

# ----------------------------------------------------------------------------
# Dependencies
# ----------------------------------------------------------------------------
include(ProjectDependencies)
fetch_project_dependencies(${BASICLOG_BUILD_TESTS})

# ----------------------------------------------------------------------------
# Compiler options
# ----------------------------------------------------------------------------
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 20)
endif()

# Disable compiler specific extensions.
set(CMAKE_CXX_EXTENSIONS OFF)

include(CompilerOptions)

set(PROJECT_COMPILER_OPTIONS_LIBRARY compile_options)
set(COMPILATION_WARNINGS_AS_ERRORS ${MAIN_PROJECT})
set_project_default_compiler_options(
    ${PROJECT_COMPILER_OPTIONS_LIBRARY}
    ${BASICLOG_PROJECT_NAME}
    ${COMPILATION_WARNINGS_AS_ERRORS}
)

# ----------------------------------------------------------------------------
# Quality tools
# ----------------------------------------------------------------------------
set(SCRIPTS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/scripts")

if(BASICLOG_ENABLE_COVERAGE)
    include(CodeCoverage)
    set(COVERAGE_EXCLUDE_PATTERNS
        "/usr/include/*"
        "/usr/local/*"
        "*/_deps/*"
        "${CMAKE_CURRENT_SOURCE_DIR}/test/*"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/examples/*"
    )
    set(MIN_LINE_COVERAGE 90)
    set(MIN_FUNCTION_COVERAGE 80)
    set(COVERAGE_JOBS 4)
    set(COVERAGE_CHECK_SCRIPT "${SCRIPTS_DIR}/coverage-report-checker.sh")
    enable_coverage(
        ${PROJECT_COMPILER_OPTIONS_LIBRARY}
        "${COVERAGE_EXCLUDE_PATTERNS}"
        ${MIN_LINE_COVERAGE}
        ${MIN_FUNCTION_COVERAGE}
        ${COVERAGE_JOBS}
        ${COVERAGE_CHECK_SCRIPT}
    )
endif()

if(BASICLOG_ENABLE_CLANG_FORMAT)
    include(ClangFormat)
    set(CLANG_FORMAT_DIRECTORIES
        "${CMAKE_CURRENT_SOURCE_DIR}/examples"
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/test"
    )
    set(CLANG_FORMAT_LOG_FILE "clang-format-report.log")
    enable_clang_format_check("${CLANG_FORMAT_DIRECTORIES}" ${CLANG_FORMAT_LOG_FILE})
endif()

if(BASICLOG_ENABLE_CLANG_TIDY)
    include(ClangTidy)
    set(CLANG_TIDY_DIRECTORIES
        "${CMAKE_CURRENT_SOURCE_DIR}/examples"
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/test"
    )
    set(CLANG_TIDY_LOG_FILE "clang-tidy-report.log")
    enable_clang_tidy("${CLANG_TIDY_DIRECTORIES}" ${CLANG_TIDY_LOG_FILE})
endif()

if(BASICLOG_ENABLE_ASAN
        OR BASICLOG_ENABLE_LSAN
        OR BASICLOG_ENABLE_TSAN
        OR BASICLOG_ENABLE_UBSAN)
    include(Sanitizers)
    enable_sanitizers(
        ${PROJECT_COMPILER_OPTIONS_LIBRARY}
        ${BASICLOG_ENABLE_ASAN}
        ${BASICLOG_ENABLE_LSAN}
        OFF
        ${BASICLOG_ENABLE_TSAN}
        ${BASICLOG_ENABLE_UBSAN}
    )
endif()

if(BASICLOG_ENABLE_DOXYGEN)
    include(DoxygenDoc)
    set(DOXYGEN_CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile.in")
    set(DOXYGEN_PROJECT "basic-log")
    set(DOXYGEN_VERSION ${BASICLOG_PROJECT_VERSION})
    set(DOXYGEN_BRIEF "A basic C++20 logging library")
    set(DOXYGEN_INPUT_LIST
        "${CMAKE_CURRENT_SOURCE_DIR}/examples"
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/src"
        "${CMAKE_CURRENT_SOURCE_DIR}/test"
    )
    string(REPLACE ";" " " DOXYGEN_INPUT "${DOXYGEN_INPUT_LIST}")
    set(DOXYGEN_OUT_DIR "${CMAKE_BINARY_DIR}/doxygen")
    set(DOXYGEN_LOG_FILE "doxygen-report.log")
    enable_doxygen_doc(
        ${DOXYGEN_CONFIG_FILE}
        ${DOXYGEN_PROJECT}
        ${DOXYGEN_VERSION}
        ${DOXYGEN_BRIEF}
        ${DOXYGEN_INPUT}
        ${DOXYGEN_OUT_DIR}
        ${DOXYGEN_LOG_FILE}
    )
endif()

# ----------------------------------------------------------------------------
# Build
# ----------------------------------------------------------------------------
add_subdirectory(include)
add_subdirectory(src)

if(BASICLOG_BUILD_TESTS)
    include(CTest)
    include(GoogleTest)
    enable_testing()
    add_subdirectory(test)
endif()

if(BASICLOG_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# ----------------------------------------------------------------------------
# Configuration report
# ----------------------------------------------------------------------------
message(STATUS)
message(STATUS "${BASICLOG_PROJECT_NAME} ${BASICLOG_PROJECT_VERSION} configuration:")
message(STATUS "- CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message(STATUS "- CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "- CMAKE_CXX_COMPILER_VERSION = ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "- CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}")
message(STATUS "- CMAKE_EXPORT_COMPILE_COMMANDS = ${CMAKE_EXPORT_COMPILE_COMMANDS}")
message(STATUS "- BASICLOG_BUILD_TESTS = ${BASICLOG_BUILD_TESTS}")
message(STATUS "- BASICLOG_BUILD_EXAMPLES = ${BASICLOG_BUILD_EXAMPLES}")
message(STATUS "- BASICLOG_ENABLE_COVERAGE = ${BASICLOG_ENABLE_COVERAGE}")
message(STATUS "- BASICLOG_ENABLE_CLANG_FORMAT = ${BASICLOG_ENABLE_CLANG_FORMAT}")
message(STATUS "- BASICLOG_ENABLE_CLANG_TIDY = ${BASICLOG_ENABLE_CLANG_TIDY}")
message(STATUS "- BASICLOG_ENABLE_ASAN = ${BASICLOG_ENABLE_ASAN}")
message(STATUS "- BASICLOG_ENABLE_LSAN = ${BASICLOG_ENABLE_LSAN}")
message(STATUS "- BASICLOG_ENABLE_TSAN = ${BASICLOG_ENABLE_TSAN}")
message(STATUS "- BASICLOG_ENABLE_UBSAN = ${BASICLOG_ENABLE_UBSAN}")
message(STATUS "- BASICLOG_ENABLE_DOXYGEN = ${BASICLOG_ENABLE_DOXYGEN}")
message(STATUS "- MAIN_PROJECT = ${MAIN_PROJECT}")
message(STATUS)
