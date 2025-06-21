project(ut_basic_log)

add_executable(${PROJECT_NAME}
    ut_basic_logger.cpp
)

gtest_discover_tests(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    PRIVATE ${BASICLOG_PROJECT_NAME}::compile_options
    PRIVATE GTest::gtest_main
    PRIVATE ${BASICLOG_PROJECT_NAME}::basic_log
    PRIVATE ${BASICLOG_PROJECT_NAME}::basic_log_utils
)
