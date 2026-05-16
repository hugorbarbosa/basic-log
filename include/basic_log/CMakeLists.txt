set(target_name "basic_log_api")
add_library(${target_name} INTERFACE)
add_library(${BASICLOG_PROJECT_NAME}::${target_name} ALIAS ${target_name})

target_sources(${target_name} PUBLIC FILE_SET HEADERS)

target_link_libraries(${target_name} INTERFACE ${BASICLOG_PROJECT_NAME}::compile_options)

target_include_directories(${target_name} INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/..)
