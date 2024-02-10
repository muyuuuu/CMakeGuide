aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

# 设置可执行文件的目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../project/inc)

add_executable(test_project ${SRC_LIST})

target_link_libraries(test_project PRIVATE project)
