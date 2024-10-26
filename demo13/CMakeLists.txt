cmake_minimum_required(VERSION 3.0)

project(HelloWorld)

add_subdirectory(src)

add_subdirectory(test)

get_property(TEST_INC GLOBAL PROPERTY  "TEST_INC")
get_property(TEST_SRC GLOBAL PROPERTY  "TEST_SRC")

message(STATUS "[MAIN] TEST_INC = ${TEST_INC}")
message(STATUS "[MAIN] TEST_SRC = ${TEST_SRC}")

include_directories(${TEST_INC})

add_executable(main ${TEST_SRC} main.cpp)