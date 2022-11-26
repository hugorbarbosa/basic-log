# ----------------------------------------------------------------------------
# Project setup
project(Logger)

# ----------------------------------------------------------------------------
# Library
add_library(${PROJECT_NAME} STATIC
    Logger.cpp
)
add_library(SimpleLogger::${PROJECT_NAME} ALIAS ${PROJECT_NAME})
