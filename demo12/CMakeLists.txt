cmake_minimum_required(VERSION 3.0)

project(HelloWorld)

add_subdirectory(modules)                                                      # 添加子目录

set(EXPORT_DIR ${CMAKE_BINARY_DIR}/export)                                     # demo5，设置导出头文件和库的路径

get_property(MODULE_INC_DIRS GLOBAL PROPERTY  "MODULE_INC_DIRS")               # 获取全局变量
get_property(MODULE_LIB_SRCS GLOBAL PROPERTY  "MODULE_LIB_SRCS")

set(ALGO_INC_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")                       # 设置根目录的头文件和源代码文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

list(APPEND ALGO_INC_DIRS "${MODULE_INC_DIRS}")                                # 添加 modules 的头文件和源代码文件
list(APPEND SRC_LIST "${MODULE_LIB_SRCS}")

include_directories(${ALGO_INC_DIRS})                                          # 参考 demo4，制作动态库

add_library(interface SHARED ${SRC_LIST})

install(TARGETS interface LIBRARY DESTINATION ${EXPORT_DIR})                   # demo5，导出库和头文件
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include DESTINATION ${EXPORT_DIR}/)

add_executable(main ${SRC_LIST} main.cpp)                                      # 生成可执行文件