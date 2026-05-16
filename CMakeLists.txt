#
# Copyright (C) 2025 Hugo Barbosa.
#

# ----------------------------------------------------------------------------
# Project setup
# ----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.28)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
     "${CMAKE_CURRENT_SOURCE_DIR}/external/cmake-modules/modules"
)
include(ProjectVersion)
get_project_version(
    VERSION_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/version/version.hpp PREFIX_OUT "BASICLOG"
)

project(
    basic_log
    VERSION ${BASICLOG_VERSION_BASE}
    LANGUAGES CXX
    DESCRIPTION "Basic logging library."
)

set(BASICLOG_PROJECT_NAME ${PROJECT_NAME})
set(BASICLOG_PROJECT_VERSION ${BASICLOG_VERSION_FULL})

# ----------------------------------------------------------------------------
# Pre-requirements
# ----------------------------------------------------------------------------
include(SourceBuilds)
validate_build_directory()

# ----------------------------------------------------------------------------
# Git information
# ----------------------------------------------------------------------------
include(GitInfo)
get_git_info("GIT_INFO")

# ----------------------------------------------------------------------------
# Configuration options
# ----------------------------------------------------------------------------
option(BASICLOG_BUILD_TESTS "Build tests" ${PROJECT_IS_TOP_LEVEL})
option(BASICLOG_BUILD_EXAMPLES "Build examples" ${PROJECT_IS_TOP_LEVEL})
option(BASICLOG_ENABLE_COVERAGE "Enable code coverage analysis" OFF)
option(BASICLOG_ENABLE_CLANG_FORMAT "Enable code formatting with clang-format" OFF)
option(BASICLOG_ENABLE_CLANG_TIDY "Enable code static analysis with clang-tidy" OFF)
option(BASICLOG_ENABLE_ASAN "Enable Address Sanitizer" OFF)
option(BASICLOG_ENABLE_LSAN "Enable Leak Sanitizer" OFF)
option(BASICLOG_ENABLE_TSAN "Enable Thread Sanitizer" OFF)
option(BASICLOG_ENABLE_UBSAN "Enable Undefined Behavior Sanitizer" OFF)
option(BASICLOG_ENABLE_DOXYGEN "Enable doxygen documentation generation" OFF)
option(BASICLOG_ENABLE_CMAKE_FORMAT "Enable CMake code formatting with cmake-format" OFF)
option(BASICLOG_ENABLE_CMAKE_LINT "Enable CMake lint with cmake-lint" OFF)

if(BASICLOG_ENABLE_COVERAGE)
    set(BASICLOG_BUILD_TESTS ON)
endif()

# ----------------------------------------------------------------------------
# CMake options
# ----------------------------------------------------------------------------
if(PROJECT_IS_TOP_LEVEL)
    if(NOT CMAKE_BUILD_TYPE)
        set(default_build_type Debug)
        message(STATUS "No build type specified, setting it to '${default_build_type}'")
        set(CMAKE_BUILD_TYPE ${default_build_type})
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

set(compiler_options_lib compile_options)
add_library(${compiler_options_lib} INTERFACE)
add_library(${BASICLOG_PROJECT_NAME}::${compiler_options_lib} ALIAS ${compiler_options_lib})
if(PROJECT_IS_TOP_LEVEL)
    add_default_compiler_options(${compiler_options_lib} WARNINGS_AS_ERRORS)
else()
    add_default_compiler_options(${compiler_options_lib})
endif()

# ----------------------------------------------------------------------------
# Quality tools
# ----------------------------------------------------------------------------

if(BASICLOG_ENABLE_COVERAGE)
    include(CodeCoverage)
    add_coverage(
        ${compiler_options_lib}
        EXCLUDE_PATTERNS
        "/usr/include/*"
        "/usr/local/*"
        "*/_deps/*"
        "${CMAKE_CURRENT_SOURCE_DIR}/test/*"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/examples/*"
        MIN_LINE_COVERAGE
        90
        MIN_FUNCTION_COVERAGE
        80
        REPORT_DIR
        "${CMAKE_BINARY_DIR}/coverage"
        PARALLEL
        8
    )
endif()

set(source_code_dirs "${CMAKE_CURRENT_SOURCE_DIR}/examples" "${CMAKE_CURRENT_SOURCE_DIR}/include"
                     "${CMAKE_CURRENT_SOURCE_DIR}/src" "${CMAKE_CURRENT_SOURCE_DIR}/test"
)

if(BASICLOG_ENABLE_CLANG_FORMAT)
    include(ClangFormat)
    add_clang_format(
        DIRECTORIES "${source_code_dirs}" LOG_FILE "${CMAKE_BINARY_DIR}/clang_format_report.log"
        CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/.clang-format"
    )
endif()

if(BASICLOG_ENABLE_CLANG_TIDY)
    include(ClangTidy)
    add_clang_tidy(
        DIRECTORIES "${source_code_dirs}" LOG_FILE "${CMAKE_BINARY_DIR}/clang_tidy_report.log"
        CONFIG_FILE "${CMAKE_CURRENT_SOURCE_DIR}/.clang-tidy"
    )
endif()

if(BASICLOG_ENABLE_ASAN
   OR BASICLOG_ENABLE_LSAN
   OR BASICLOG_ENABLE_TSAN
   OR BASICLOG_ENABLE_UBSAN
)
    include(Sanitizers)
    add_sanitizers(
        ${compiler_options_lib}
        ASAN
        ${BASICLOG_ENABLE_ASAN}
        LSAN
        ${BASICLOG_ENABLE_LSAN}
        TSAN
        ${BASICLOG_ENABLE_TSAN}
        UBSAN
        ${BASICLOG_ENABLE_UBSAN}
        MSAN
        OFF
    )
endif()

if(BASICLOG_ENABLE_DOXYGEN)
    include(Doxygen)
    add_doxygen(
        DOXYFILE_IN
        "${CMAKE_CURRENT_SOURCE_DIR}/doxygen/Doxyfile.in"
        DOXYGEN_PROJECT_NAME
        "basic-log"
        DOXYGEN_PROJECT_NUMBER
        ${BASICLOG_PROJECT_VERSION}
        DOXYGEN_PROJECT_BRIEF
        "A basic C++20 logging library"
        DOXYGEN_INPUT
        "${source_code_dirs}"
        DOXYGEN_OUTPUT_DIRECTORY
        "${CMAKE_BINARY_DIR}/doxygen"
        LOG_FILE
        "${CMAKE_BINARY_DIR}/doxygen_report.log"
    )
endif()

if(BASICLOG_ENABLE_CMAKE_FORMAT)
    include(CmakeFormat)
    add_cmake_format(
        DIRECTORIES
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
        "${source_code_dirs}"
        EXTRA_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt"
        LOG_FILE
        "${CMAKE_BINARY_DIR}/cmake_format_report.log"
        CONFIG_FILE
        "${CMAKE_CURRENT_SOURCE_DIR}/.cmake-format.py"
    )
endif()

if(BASICLOG_ENABLE_CMAKE_LINT)
    include(CmakeLint)
    add_cmake_lint(
        DIRECTORIES
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake"
        "${source_code_dirs}"
        EXTRA_FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/CMakeLists.txt"
        LOG_FILE
        "${CMAKE_BINARY_DIR}/cmake_lint_report.log"
        CONFIG_FILE
        "${CMAKE_CURRENT_SOURCE_DIR}/.cmake-format.py"
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
message(STATUS "- PROJECT_IS_TOP_LEVEL = ${PROJECT_IS_TOP_LEVEL}")
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
message(STATUS "- BASICLOG_ENABLE_CMAKE_FORMAT = ${BASICLOG_ENABLE_CMAKE_FORMAT}")
message(STATUS "- BASICLOG_ENABLE_CMAKE_LINT = ${BASICLOG_ENABLE_CMAKE_LINT}")
message(STATUS)
