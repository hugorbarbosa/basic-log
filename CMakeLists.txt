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

# Build type (configuration) on multi-config generators (e.g. Visual Studio, Xcode, or Ninja Multi-Config).
# Set default configuration type if configuration type not set.
if (NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_CONFIGURATION_TYPES Debug)
endif()

# ----------------------------------------------------------------------------
# Dependencies

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Fetch dependencies
include(FetchDependencies)

# ----------------------------------------------------------------------------
# Test

if (BUILD_TESTS)
    include(CTest)
    include(GoogleTest)
    enable_testing()
endif()

# ----------------------------------------------------------------------------
# Build

# C++ standard
set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compile options for GCC
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} -Wall -Werror"
    )
endif()

# Set compile options for MSVC
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS
        "${CMAKE_CXX_FLAGS} /WX"
    )
endif()

# Subdirectories
add_subdirectory(src)
if (BUILD_TESTS)
    add_subdirectory(tests)
endif()

# ----------------------------------------------------------------------------
# Status
message(STATUS)
message(STATUS "${PROJECT_NAME} configuration:")
message(STATUS "- CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message(STATUS "- CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "- CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}")
# message(STATUS "- CMAKE_CXX_FLAGS = ${CMAKE_CXX_FLAGS}")
message(STATUS "- BUILD_TESTS = ${BUILD_TESTS}")
message(STATUS)
