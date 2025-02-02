cmake_minimum_required(VERSION 3.16)

# TODO: Use "target_compile_options" instead of "add_compile_options".

# Set the compiler options.
function(set_compiler_options)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        add_compile_options(
            /W4 # Displays level 1 to level 4 (informational) warnings.
            /WX # Treat warnings as errors.
        )
    else()
        add_compile_options(
            -Wall # Enable most warning messages.
            -Werror # Make all warnings into errors.
        )
    endif()
endfunction()
