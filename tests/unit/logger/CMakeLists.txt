# ----------------------------------------------------------------------------
# Project setup
project(LoggerTest)

enable_testing()

# ----------------------------------------------------------------------------
# Executable
add_executable(${PROJECT_NAME}
    LoggerTest.cpp
)

# ----------------------------------------------------------------------------
# Tests
gtest_discover_tests(${PROJECT_NAME})

# ----------------------------------------------------------------------------
# Build

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_SOURCE_DIR}/src
    # PRIVATE ${CMAKE_SOURCE_DIR}/tests
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE GTest::gtest_main
    # PRIVATE GTest::gmock
    PRIVATE SimpleLogger::Logger
)
