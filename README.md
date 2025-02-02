# basic-log

A basic C++ logging library, based on the `std::ostream` of the C++ Standard Library.

**Note:** If you are looking for a feature-rich and more tested library, please do not use this library. It was developed only as part of my studies.

## Table of contents

- [Features](#features)
- [Examples](#examples)
- [Integration](#integration)
- [Supported compilers](#supported-compilers)
- [Compilation](#compilation)
- [Running the examples](#running-the-examples)
- [Tests](#tests)
- [License](#license)

## Features

This library is a very basic facility that allows logging of messages during the execution of a program. The following are the features provided by this library:

- Since it is based on the `std::ostream`, the user can easily choose the output stream to log messages: console, file, etc.
- Provides the following logging levels:
    - *None*: no logging (calling any function to log a message has no effect).
    - *Fatal*: logs only fatal messages.
    - *Error*: logs error messages and higher level messages (only error and fatal messages are logged in this case).
    - *Warning*: logs warnings messages and higher level messages.
    - *Info*: logs information messages and higher level messages.
    - *Debug*: logs debug messages and higher level messages.
    - *Verbose*: logs verbose messages and higher level messages.
- Format of the output is `[index][YYYY-MM-DD HH:MM:SS.MMM][level][Tn] Message`, where:
    - `index`: message index (counter).
    - `YYYY-MM-DD HH:MM:SS.MMM`: date and time.
    - `level`: logging level of the message.
    - `Tn`: thread ID of the thread from which the message was logged (e.g., `T42`).
    - `Message`: logged message.

## Examples

The following is an example of how to log messages using this logging library. In this case, messages are directed to the standard output stream.

```c++
#include <basic_log/basic_logger.h>
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

This library creates a CMake target that can be linked in your project, and there are many ways to make this library available to be used in your project.

### Using CMake `FetchContent` module

CMake `FetchContent` module can be used to automatically download this library as a dependency when configuring your project. For that, you just need to place this code in your `CMakeLists.txt` file:

```cmake
include(FetchContent)
FetchContent_Declare(
    basiclog
    GIT_REPOSITORY https://github.com/hugorbarbosa/basic-log
    GIT_TAG main # Or a commit hash if you prefer
)
FetchContent_MakeAvailable(basiclog)
# ...
target_link_libraries(your-target PRIVATE basic_log::basic_log)
```

### Copying the entire project

You can copy the entire project source tree into your project, and in your `CMakeLists.txt` file:

```cmake
add_subdirectory(basic-log)
# ...
target_link_libraries(your-target PRIVATE basic_log::basic_log)
```

### Using as `git submodule`

You can also use this library as a `git submodule` in your project. For this case, the CMake code needed is the same as the one demonstrated if this entire project was copied into your project.

## Supported compilers

This project can be successfully compiled using the following compilers (it might also compile using other):

- GCC 9.4.0
- Microsoft Visual C++ 2022 / Build Tools 19.41.34123

## Compilation

The following commands can be utilized to configure the project (example for Debug configuration):

```sh
$ cd <project-directory>
$ mkdir build-debug
$ cd build-debug
$ cmake .. -DCMAKE_BUILD_TYPE=Debug
```

To compile the software, you can use the CMake build command:

```sh
$ cmake --build . -j 8
```

## Running the examples

If you want to run the examples of how to use this library, it is necessary to configure the project as follows:

```sh
$ cd build-debug
$ cmake .. -DCMAKE_BUILD_TYPE=Debug -DBASICLOG_BUILD_EXAMPLES=ON
$ cmake --build . -j 8
```

After compiling the project, an executable file is created and can be run using the following command (note that some configuration generators (e.g., Visual Studio) may add a configuration folder (e.g., Debug) in the path):

```sh
$ ./bin/<config>/basic-log-example
```

## Tests

To run the unit tests, use the commands below:

```sh
$ cd build-debug
$ cmake .. -DCMAKE_BUILD_TYPE=Debug -DBASICLOG_BUILD_TESTS=ON
$ cmake --build . -j 8
$ ctest
```

## License

Licensed under the [MIT license](./LICENSE).
