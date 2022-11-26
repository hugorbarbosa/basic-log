# ----------------------------------------------------------------------------
# Project setup
project(SimpleLogger)

# Subdirectories
add_subdirectory(logger)

# ----------------------------------------------------------------------------
# Executable
add_executable(${PROJECT_NAME}
    main.cpp
)

# ----------------------------------------------------------------------------
# Build

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE SimpleLogger::Logger
)
