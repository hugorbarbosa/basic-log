# ----------------------------------------------------------------------------
# Project setup
project(MockLogger)

# ----------------------------------------------------------------------------
# Library
add_library(${PROJECT_NAME} STATIC
    MockLogger.h
)
add_library(SimpleLogger::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

# ----------------------------------------------------------------------------
# Build

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE GTest::gmock
    PRIVATE SimpleLogger::Logger
)
