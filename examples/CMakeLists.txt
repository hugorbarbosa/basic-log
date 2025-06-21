project(basic-log-example)

add_executable(${PROJECT_NAME}
    examples.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE ${BASICLOG_PROJECT_NAME}::compile_options
    PRIVATE basic_log::basic_log
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
