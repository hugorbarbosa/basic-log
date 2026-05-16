set(target_name "basic_log")
add_library(${target_name})
add_library(${BASICLOG_PROJECT_NAME}::${target_name} ALIAS ${target_name})

target_sources(${target_name} PRIVATE basic_logger.cpp)

target_link_libraries(
    ${target_name}
    PRIVATE ${BASICLOG_PROJECT_NAME}::compile_options ${BASICLOG_PROJECT_NAME}::basic_log_utils
    PUBLIC ${BASICLOG_PROJECT_NAME}::basic_log_api
)
