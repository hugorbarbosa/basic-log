# ----------------------------------------------------------------------------
# Project setup

cmake_minimum_required(VERSION 3.16)

project(SimpleLogger
    VERSION 1.0.0
    LANGUAGES CXX
)

# ----------------------------------------------------------------------------
# Configuration options

# Option to build unit tests
option(BUILD_TESTS "Build unit tests" OFF)

# ----------------------------------------------------------------------------
# CMake options

# Build type on single-configuration generators (e.g. Makefile generators or Ninja).
# Set default build type if build type not set.
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# ----------------------------------------------------------------------------
# Dependencies

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Fetch dependencies
include(FetchDependencies)

# ----------------------------------------------------------------------------
# Build

# C++ standard
set(CMAKE_CXX_STANDARD 20)

# Compiler options
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    # GCC compiler options
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    # MSVC compiler options
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /WX")
endif()

# Subdirectories
add_subdirectory(src)
if (BUILD_TESTS)
    include(CTest)
    include(GoogleTest)
    enable_testing()
    add_subdirectory(tests)
endif()

# ----------------------------------------------------------------------------
# Status
message(STATUS)
message(STATUS "${PROJECT_NAME} configuration:")
message(STATUS "- CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message(STATUS "- CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "- CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}")
message(STATUS "- BUILD_TESTS = ${BUILD_TESTS}")
message(STATUS)
