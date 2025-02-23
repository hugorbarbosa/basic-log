/**
 * @file
 * @copyright Copyright (C) 2025 Hugo Barbosa.
 */

#include <basic_log/basic_logger.hpp>
#include <iostream>

/**
 * @brief Example of message logging to console.
 */
void console_log_example() noexcept
{
    basic_log::BasicLogger console_logger{std::cout};

    console_logger.info("Setting logging level to verbose...");
    console_logger.set_log_level(basic_log::LogLevel::verbose);

    console_logger.fatal("This is a fatal message");
    console_logger.error("This is an error message");
    console_logger.warning("Warning message is here!");
    console_logger.info("This is a message to inform something");
    console_logger.debug("A message for debugging purposes");
    console_logger.verbose("Now a message logged with the verbose level");

    console_logger.info("Changing logging level to info...");
    console_logger.set_log_level(basic_log::LogLevel::info);

    console_logger.info(
        "We will try to log debug and verbose messages, but they will not be logged");
    console_logger.debug("Debug message that is not logged");
    console_logger.verbose("And this message is not logged too");
    console_logger.fatal("But fatal messages are still logged");
    console_logger.error("And also error messages");
    console_logger.warning("And also warning messages");

    console_logger.info("Changing logging level to verbose again...");
    console_logger.set_log_level(basic_log::LogLevel::verbose);
    console_logger.debug("Now debug messages are logged again");
    console_logger.verbose("And verbose messages too");
}

/**
 * @brief Main function.
 *
 * @return Program exit code.
 */
int main()
{
    console_log_example();
    // TODO: Add example that logs messages to a file.

    return EXIT_SUCCESS;
}
