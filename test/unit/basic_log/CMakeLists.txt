set(target_name "ut_basic_log")
add_executable(${target_name})

target_sources(${target_name} PRIVATE ut_basic_logger.cpp)

target_link_libraries(
    ${target_name}
    PRIVATE GTest::gtest_main ${BASICLOG_PROJECT_NAME}::compile_options
            ${BASICLOG_PROJECT_NAME}::basic_log ${BASICLOG_PROJECT_NAME}::basic_log_utils
)

gtest_discover_tests(${target_name})
