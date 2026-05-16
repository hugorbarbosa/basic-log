set(target_name "basic-log-example")
add_executable(${target_name})

target_sources(${target_name} PRIVATE examples.cpp)

target_link_libraries(
    ${target_name} PRIVATE ${BASICLOG_PROJECT_NAME}::compile_options basic_log::basic_log
)

set_target_properties(${target_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
