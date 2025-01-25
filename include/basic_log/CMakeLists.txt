project(basic_log_api)

add_library(${PROJECT_NAME} INTERFACE)
add_library(${BASICLOG_PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    INTERFACE ${BASICLOG_INCLUDE_DIR}
)
