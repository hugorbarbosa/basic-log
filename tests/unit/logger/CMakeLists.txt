# ----------------------------------------------------------------------------
# Project setup
project(LoggerTest)

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
target_link_libraries(${PROJECT_NAME}
    PRIVATE GTest::gtest_main
    PRIVATE SimpleLogger::Logger
)
