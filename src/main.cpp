/**
 * @file
 * @copyright Copyright (c) 2022-2023.
 */

#include <iostream>
#include <Logger.h>

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
    using namespace logger;

    // Logger instance
    std::unique_ptr<ILogger> logger{std::make_unique<Logger>(std::cout)};

    // Log level
    logger->setLogLevel(ILogger::LogLevel::VERBOSE);

    // Messages with different log levels
    logger->logFatal("Fatal message");
    logger->logError("Error message");
    logger->logWarning("Warning message");
    logger->logInfo("Info message");
    logger->logDebug("Debug message");
    logger->logVerbose("Verbose message");

    return EXIT_SUCCESS;
}
