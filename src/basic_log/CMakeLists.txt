project(basic_log)

add_library(${PROJECT_NAME} STATIC
    basic_logger.cpp
)
add_library(${BASICLOG_PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}
    PUBLIC ${BASICLOG_PROJECT_NAME}::basic_log_api
    PRIVATE ${BASICLOG_PROJECT_NAME}::basic_log_utils
)
