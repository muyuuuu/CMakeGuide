cmake_minimum_required(VERSION 3.0)

project(HelloWorld)

add_definitions(-DTEST)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/install)

add_executable(main main.cpp)