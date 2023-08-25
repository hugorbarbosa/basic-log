# C++ logger

A simple logger implemented in C++.

## Table of contents

- [Project structure](#project-structure)
- [Features](#features)
- [Requirements](#requirements)
- [Compilation](#compilation)
- [Running](#running)
- [Tests](#tests)
- [License](#license)

## Project structure

This project is structured in the following directories:

- `cmake`: useful CMake files.
- `docs`: project documentation.
- `src`: source code of the project.
- `tests`: files related with tests.

## Features

The logger of this project is a simple logger that allows to log messages during the execution of a program. This log uses a stream of type `std::ostream`, so the user can choose the output stream to log messages (console, file, etc).

The logger features the following levels:

- *None*: there's no logging (calling any method to log a message has no effect).
- *Fatal*: logs only fatal messages.
- *Error*: logs error messages and higher level messages (for example, if the logger is defined with this level, fatal messages are also logged but warning messages are ignored).
- *Warning*: logs warnings messages and higher level messages.
- *Info*: logs information messages and higher level messages.
- *Debug*: logs debug messages and higher level messages.
- *Verbose*: logs verbose messages and higher level messages.

The format of the output is the following:

```
[YYYY-MM-DD HH:MM:SS][Level] Message
```

The logger is implemented [here](./src/logger/). An example of how to use it can be seen in the following code snippet (extracted from [here](./src/main.cpp)).

```C++
#include <iostream>
#include <Logger.h>

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
```

This example uses `std::cout` as output stream, and its result is illustrated in the figure below.

!["Example"](./docs/assets/example-log.png)

## Requirements

Necessary tools:

- CMake: system to manage the build process.
- C++ compiler: for software compilation.

## Compilation

The CMake options for configuration of this project are:

| CMake option | Description | Default value |
| --- | --- | --- |
| BUILD_TESTS | Build unit tests | OFF |

The following commands can be utilized to configure the project (example for Debug configuration):

```sh
$ cd <project-directory>
$ mkdir build-debug
$ cd build-debug
$ cmake .. -DCMAKE_BUILD_TYPE=Debug
```

To compile the software, use the following command:

```sh
$ cmake --build . -j 4
```

## Running

After compiling the project, an executable file is created and can be run using the following command (note that some configuration generators (e.g., Visual Studio) may add a configuration folder (e.g., Debug) in the path):

```sh
$ ./bin/<config>/SimpleLogger
```

## Tests

To run the unit tests, use the commands below (note that it is necessary to configure CMake with `BUILD_TESTS` option to ON):

```sh
$ cd <project-directory>
$ mkdir build-debug
$ cd build-debug
$ cmake .. -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON
$ cmake --build . -j 4
$ ctest
```

## License

Licensed under the [MIT license](./LICENSE).
