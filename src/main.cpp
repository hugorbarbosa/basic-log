/**
 * @file
 * @copyright Copyright (c) 2022-2023.
 */

#include <iostream>
#include <logger/Logger.h>

/**
 * @brief Main function.
 *
 * @param argc Number of command line arguments.
 * @param argv Command line arguments.
 *
 * @return Program exit code.
 */
int main([[maybe_unused]] int argc, [[maybe_unused]] char const* argv[])
{
    // Logger instance
    logger::Logger logger{std::cout};

    // Log level
    logger.setLogLevel(logger::Logger::LogLevel::VERBOSE);

    // Messages with different log levels
    logger.logFatal("Fatal message");
    logger.logError("Error message");
    logger.logWarning("Warning message");
    logger.logInfo("Info message");
    logger.logDebug("Debug message");
    logger.logVerbose("Verbose message");

    return EXIT_SUCCESS;
}
