# basic-log

A basic C++20 logging library, based on the `std::ostream` of the C++ Standard Library.

## Table of contents

- [Features](#features)
- [Requirements](#requirements)
    - [Using Docker](#using-docker)
- [Examples](#examples)
- [Integration](#integration)
- [Supported compilers](#supported-compilers)
- [Building](#building)
- [Running the examples](#running-the-examples)
- [Tests](#tests)
- [Code coverage](#code-coverage)
- [Coding style and format](#coding-style-and-format)
- [Code static analysis](#code-static-analysis)
- [Sanitizers](#sanitizers)
    - [Address sanitizer](#address-sanitizer)
    - [Leak sanitizer](#leak-sanitizer)
    - [Thread sanitizer](#thread-sanitizer)
    - [Undefined behavior sanitizer](#undefined-behavior-sanitizer)
- [Source code documentation](#source-code-documentation)
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

**Note:** If you are looking for a feature-rich and more tested library, this probably won't be the most suitable library for your needs. It was developed only as part of my studies.

## Requirements

The following tools are used by this project:

- CMake: system to manage the build process.
- C++ compiler: for software compilation (examples: Microsoft Visual C++, GCC and Clang).
- LCOV: to obtain the code coverage report.
- Clang-format: for code formatting.
- Clang-tidy: for code static analysis.
- Doxygen: for generation of documentation from source code.

### Using Docker

There is a Docker image available in this project that contains all the dependencies to compile and run this software, as well as the required tools. This allows to quickly use this project without installing any tool in the local machine.

The instructions to use the docker image can be found [here](./docker/README.md).

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

This project can be successfully built using the following compilers (it might also succeed using another one):

- Clang 18.1.3
- GCC 13.3.0
- Microsoft Visual C++ 2022 / Build Tools 19.43.34808.0

## Building

The following commands can be utilized to configure and compile the project (example for Debug build type):

```sh
$ cd <project-directory>
$ cmake -S . -B ./build-debug -DCMAKE_BUILD_TYPE=Debug
$ cmake --build ./build-debug -j 4
```

This project provides this [CMakePresets.json](./CMakePresets.json) file, which specifies some common configuration options to facilitate the building of the project and the sharing of these settings with the developers/users. The previous configure and build commands can be replaced by the following preset commands, using the GCC compiler in this case but there are more compiler options available in the JSON file:

```sh
$ cd <project-directory>
$ cmake --preset debug-gcc
$ cmake --build --preset debug-gcc
```

To list all the CMake configuration presets available for this project, use the following commands:

```sh
$ cd <project-directory>
$ cmake --list-presets=configure
$ cmake --list-presets=build
$ cmake --list-presets=test
```

## Running the examples

If you want to run the examples of how to use this library, it is necessary to configure and build the project as follows:

```sh
$ cd <project-directory>
$ cmake -S . -B ./build-examples -DBASICLOG_BUILD_EXAMPLES=ON
$ cmake --build ./build-examples -j 4
```

Alternatively, use CMake presets as follows to build the examples:

```sh
$ cd <project-directory>
$ cmake --preset examples
$ cmake --build --preset examples
```

After compiling the project, an executable file is created and can be run using the following command (note that some configuration generators (e.g., Visual Studio) may add a configuration folder (e.g., Debug) in the path):

```sh
$ cd <build-directory>
$ ./bin/<config>/basic-log-example
```

## Tests

To compile and run the tests, use the commands below:

```sh
$ cd <project-directory>
$ mkdir build-debug
$ cd build-debug
$ cmake .. -DCMAKE_BUILD_TYPE=Debug -DBASICLOG_BUILD_TESTS=ON
$ cmake --build . -j 4
$ ctest
```

Alternatively, CMake presets can be applied as follows to run the tests:

```sh
$ cd <project-directory>
$ cmake --preset debug-gcc
$ cmake --build --preset debug-gcc
$ ctest --preset debug-gcc
```

## Code coverage

The project can be compiled for code coverage analysis (with GCC compiler only), using the following commands:

```sh
$ cd <project-directory>
$ mkdir build-coverage
$ cd build-coverage
$ cmake .. -DCMAKE_BUILD_TYPE=Debug -DBASICLOG_ENABLE_COVERAGE=ON
$ cmake --build . --target coverage
```

CMake presets may be utilized instead of the previous commands to run code coverage analysis:

```sh
$ cd <project-directory>
$ cmake --preset coverage
$ cmake --build --preset coverage
```

This target compiles and generates a report with the code coverage analysis, using the LCOV tool. This report is placed inside of the build directory (`build-coverage` in this example), being available in `coverage/index.html`.

Additionally, this target also verifies the code coverage percentage and succeeds or fails if the coverage is sufficient or not, respectively. The accepted coverage percentage value is configured by CMake.

## Coding style and format

This projects follows my [C++ coding style guide](https://github.com/hugorbarbosa/cpp-coding-style-guide). To ensure consistency, the format of the code can be checked using the commands below:

```sh
$ cd <project-directory>
$ mkdir build-clang-format
$ cd build-clang-format
$ cmake .. -DBASICLOG_ENABLE_CLANG_FORMAT=ON
$ cmake --build . --target clang_format
```

Alternatively, use CMake presets as follows to check the code format:

```sh
$ cd <project-directory>
$ cmake --preset clang-format
$ cmake --build --preset clang-format
```

This target uses clang-format to verify the format of the code, and creates a report file in the `build-clang-format` directory (used build directory in this example), named as `clang-format-report.log`.

The build succeeds only if the source files are formatted accordingly to the [configuration](.clang-format) file. The project source files to be verified are configured by CMake.

## Code static analysis

Clang-tidy is a tool that can be used to perform code static analysis. The project is prepared to execute this type of analysis using this tool, applying the following commands:

```sh
$ cd <project-directory>
$ mkdir build-clang-tidy
$ cd build-clang-tidy
$ cmake .. -DCMAKE_BUILD_TYPE=Debug -DBASICLOG_ENABLE_CLANG_TIDY=ON -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++
$ cmake --build . --target clang_tidy
```

Alternatively to using the previous commands, CMake presets may be applied to facilitate the build to perform static analysis using clang-tidy:

```sh
$ cd <project-directory>
$ cmake --preset clang-tidy
$ cmake --build --preset clang-tidy
```

This target runs clang-tidy and generates a report with the results of the code static analysis, named as `clang-tidy-report.log` and placed inside of the build directory (`build-clang-tidy` in this example).

The build succeeds only if no issues are found during the code static analysis, which utilizes the list of checks provided in the respective [configuration](.clang-tidy) file. The project source files to be analyzed are configured by CMake.

## Sanitizers

### Address sanitizer

AddressSanitizer (ASan) can be enabled using the following commands:

```sh
$ cd <project-directory>
$ mkdir build-sanitizer-address
$ cd build-sanitizer-address
$ cmake .. -DCMAKE_BUILD_TYPE=Debug -DBASICLOG_BUILD_TESTS=ON -DBASICLOG_ENABLE_ASAN=ON
$ cmake --build . -j 4
$ ctest
```

Alternatively, CMake presets can be used as follows to enable this sanitizer:

```sh
$ cd <project-directory>
$ cmake --preset sanitizer-address
$ cmake --build --preset sanitizer-address
$ ctest --preset sanitizer-address
```

### Leak sanitizer

LeakSanitizer (LSan) can be enabled using the following commands:

```sh
$ cd <project-directory>
$ mkdir build-sanitizer-leak
$ cd build-sanitizer-leak
$ cmake .. -DCMAKE_BUILD_TYPE=Debug -DBASICLOG_BUILD_TESTS=ON -DBASICLOG_ENABLE_LSAN=ON
$ cmake --build . -j 4
$ ctest
```

Alternatively, CMake presets can be used as follows to enable this sanitizer:

```sh
$ cd <project-directory>
$ cmake --preset sanitizer-leak
$ cmake --build --preset sanitizer-leak
$ ctest --preset sanitizer-leak
```

### Thread sanitizer

ThreadSanitizer (TSan) can be enabled using the following commands:

```sh
$ cd <project-directory>
$ mkdir build-sanitizer-thread
$ cd build-sanitizer-thread
$ cmake .. -DCMAKE_BUILD_TYPE=Debug -DBASICLOG_BUILD_TESTS=ON -DBASICLOG_ENABLE_TSAN=ON
$ cmake --build . -j 4
$ ctest
```

Alternatively, CMake presets can be used as follows to enable this sanitizer:

```sh
$ cd <project-directory>
$ cmake --preset sanitizer-thread
$ cmake --build --preset sanitizer-thread
$ ctest --preset sanitizer-thread
```

### Undefined behavior sanitizer

UndefinedBehaviorSanitizer (UBSan) can be enabled using the following commands:

```sh
$ cd <project-directory>
$ mkdir build-sanitizer-undefined
$ cd build-sanitizer-undefined
$ cmake .. -DCMAKE_BUILD_TYPE=Debug -DBASICLOG_BUILD_TESTS=ON -DBASICLOG_ENABLE_UBSAN=ON
$ cmake --build . -j 4
$ ctest
```

Alternatively, CMake presets can be used as follows to enable this sanitizer:

```sh
$ cd <project-directory>
$ cmake --preset sanitizer-undefined
$ cmake --build --preset sanitizer-undefined
$ ctest --preset sanitizer-undefined
```

## Source code documentation

Doxygen is used to generate documentation from source code, and the commands below can be used for that purpose:

```sh
$ cd <project-directory>
$ mkdir build-doxygen
$ cd build-doxygen
$ cmake .. -DBASICLOG_ENABLE_DOXYGEN=ON
$ cmake --build . --target doxygen
```

The respective CMake presets can be used instead of the previous commands to run doxygen:

```sh
$ cd <project-directory>
$ cmake --preset doxygen
$ cmake --build --preset doxygen
```

This target generates documentation from the source files using doxygen, in the `build-doxygen` directory (used build directory in this example), which can be accessed from `html/index.html`. Furthermore, a report file named as `doxygen-report.log` is also created in this build directory.

This target only succeeds if the source files are correctly documented. The doxygen [configuration](./doxygen/Doxyfile.in) file in this project is prepared to be automatically configured through CMake.

## License

Licensed under the [MIT license](./LICENSE).
