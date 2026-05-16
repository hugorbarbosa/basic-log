# basic-log

A basic C++20 logging library, based on the `std::ostream` of the C++ Standard Library.

## Table of contents

- [Features](#features)
- [Building](#building)
- [Examples](#examples)
- [Integration](#integration)
- [License](#license)

## Features

This library is a very basic facility that allows logging of messages during the execution of a program. The following are the features provided by this library:

- Since it is based on the `std::ostream`, the user can easily choose the output stream to log messages: console, file, etc.
- Supports the following logging levels:
    - *None*: disables logging entirely (all logging calls are ignored).
    - *Fatal*: logs fatal messages only.
    - *Error*: logs error and higher-severity messages.
    - *Warning*: logs warning and higher-severity messages.
    - *Info*: logs informational and higher-severity messages.
    - *Debug*: logs debug and higher-severity messages.
    - *Verbose*: logs all messages, including verbose diagnostics.
- Format of the output is `[index][YYYY-MM-DD HH:MM:SS.MMM][level][Tn] Message`, where:
    - `index`: message index (counter).
    - `YYYY-MM-DD HH:MM:SS.MMM`: date and time.
    - `level`: logging level of the message.
    - `Tn`: thread ID of the thread from which the message was logged (e.g., `T42`).
    - `Message`: logged message.

**Note:** If you are looking for a feature-rich and more tested library, this library probably won't be the most suitable one for your needs. It was developed only as part of my studies.

## Building

This project uses CMake as its build system, with support for CMake Presets to simplify configuration and building.

For detailed build instructions, including how to build the project, run tests, enable optional code quality tools (code coverage, code formatting, sanitizers, static analysis, etc) and generate documentation, please see the [Building guide](BUILDING.md).

## Examples

The following is an example of how to log messages using this logging library. In this case, messages are directed to the standard output stream.

```c++
#include <basic_log/basic_logger.hpp>
#include <iostream>

int main()
{
    // Basic logger instance that uses the standard output stream.
    basic_log::BasicLogger logger{std::cout};

    logger.set_log_level(basic_log::LogLevel::verbose);

    logger.fatal("Fatal message");
    logger.error("Error message");
    logger.warning("Warning message");
    logger.info("Info message");
    logger.debug("Debug message");
    logger.verbose("Verbose message");

    return EXIT_SUCCESS;
}
```

The console will have similar messages to the following ones when running this example:

```sh
[1][2025-01-01 09:10:11.234][fatal][T42] Fatal message
[2][2025-01-01 09:10:11.236][error][T42] Error message
[3][2025-01-01 09:10:11.238][warning][T42] Warning message
[4][2025-01-01 09:10:11.240][info][T42] Info message
[5][2025-01-01 09:10:11.242][debug][T42] Debug message
[6][2025-01-01 09:10:11.244][verbose][T42] Verbose message
```

For more usage examples, please explore the [examples](./examples) directory.

## Integration

This library creates a CMake target that can be linked in your project, and there are many ways to make this library available for that.

### Using CMake `FetchContent` feature

CMake `FetchContent` feature can be used to automatically download this library as a dependency when configuring your project. For that, you just need to place this code in your `CMakeLists.txt` file:

```cmake
include(FetchContent)
FetchContent_Declare(
    basiclog
    GIT_REPOSITORY https://github.com/hugorbarbosa/basic-log
    GIT_TAG <tag> # Tag, branch or commit hash.
)
FetchContent_MakeAvailable(basiclog)
# ...
target_link_libraries(your-target PRIVATE basic_log::basic_log)
```

### Using as `git submodule`

You can use this library as a `git submodule` in your project. For this case, you need to configure the submodule as follows (the example places the library in the `external` directory inside of your project):

```sh
git submodule add https://github.com/hugorbarbosa/basic-log external/basic-log
```

With the previous command, a `.gitmodules` file is created and the library is available in your project. You can select a specific tag, branch or commit hash of the library that you want to use from its directory.

With this option, you need to update the submodule for setting up your project:

```sh
git submodule update --init --recursive
```

Additionally, the following code shall be added to your `CMakeLists.txt` file to use the library:

```cmake
add_subdirectory(external/basic-log)
# ...
target_link_libraries(your-target PRIVATE basic_log::basic_log)
```

### Copying the entire project

You can also copy the entire project source tree into your project. For this case, the code to be added to your `CMakeLists.txt` file is the same as the one demonstrated for when the library is used as a `git submodule`.

## License

Licensed under the [MIT license](./LICENSE).
