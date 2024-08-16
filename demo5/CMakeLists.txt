cmake_minimum_required(VERSION 3.0)

project(HelloWorld)

# 头文件
include_directories(${PROJECT_SOURCE_DIR}/inc)

# 源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

# 设置动态库/静态库生成路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)

# 制作静态库
# add_library(info STATIC ${SRC_LIST})

# 制作动态库
add_library(info SHARED ${SRC_LIST})

set(EXPORT_DIR ${CMAKE_BINARY_DIR}/export)                                # 设置导出路径
install(TARGETS info LIBRARY DESTINATION ${EXPORT_DIR})                   # 导出 info 库到 build/export
install(DIRECTORY ${PROJECT_SOURCE_DIR}/inc DESTINATION ${EXPORT_DIR}/)   # 将头文件导出到 build/export/