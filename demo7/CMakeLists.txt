cmake_minimum_required(VERSION 3.0)

project(HelloWorld)

message(STATUS "======= ${PROJECT_SOURCE_DIR}")
# 头文件
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(main  main.cpp)