cmake_minimum_required(VERSION 3.0)

project(HelloWorld)

set(CODE_LIST info1.cpp info2.cpp info3.cpp main.cpp)

add_executable(main ${CODE_LIST})