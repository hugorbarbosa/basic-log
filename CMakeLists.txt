# ----------------------------------------------------------------------------
# Project setup
# ----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.16)

project(basic_log
    VERSION 1.0.0
    LANGUAGES CXX
    DESCRIPTION "Basic logging library."
)

set(BASICLOG_PROJECT_NAME ${PROJECT_NAME})
set(BASICLOG_PROJECT_VERSION ${PROJECT_VERSION})

set(MAIN_PROJECT OFF)
if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
    set(MAIN_PROJECT ON)
endif()

# ----------------------------------------------------------------------------
# Configuration options
# ----------------------------------------------------------------------------
option(BASICLOG_BUILD_TESTS "Build tests" ${MAIN_PROJECT})
option(BASICLOG_BUILD_EXAMPLES "Build examples" ${MAIN_PROJECT})

# ----------------------------------------------------------------------------
# CMake options
# ----------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# ----------------------------------------------------------------------------
# Dependencies
# ----------------------------------------------------------------------------
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})
include(FetchDependencies)

# ----------------------------------------------------------------------------
# Build
# ----------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 20)

include(CompilerOptions)
set_compiler_options()

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
# Status
# ----------------------------------------------------------------------------
message(STATUS)
message(STATUS "${BASICLOG_PROJECT_NAME} ${BASICLOG_PROJECT_VERSION} configuration:")
message(STATUS "- CMAKE_BUILD_TYPE = ${CMAKE_BUILD_TYPE}")
message(STATUS "- CMAKE_CXX_COMPILER_ID = ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "- CMAKE_CXX_STANDARD = ${CMAKE_CXX_STANDARD}")
message(STATUS "- BASICLOG_BUILD_TESTS = ${BASICLOG_BUILD_TESTS}")
message(STATUS "- BASICLOG_BUILD_EXAMPLES = ${BASICLOG_BUILD_EXAMPLES}")
message(STATUS)
