cmake_minimum_required(VERSION 3.0)

project(HelloWorld)

message(STATUS "======= ${PROJECT_SOURCE_DIR}")
# 头文件
include_directories(${PROJECT_SOURCE_DIR}/inc)

message(STATUS "======= ${CMAKE_CURRENT_SOURCE_DIR}")
# 源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

add_executable(main ${SRC_LIST} main.cpp)