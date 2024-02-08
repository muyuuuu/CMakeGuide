cmake_minimum_required(VERSION 3.0)

if(CMAKE_BUILD_TYPE MATCHES "(Release|RELEASE|release)")
    add_definitions(-DRELEASE)
else()
    add_definitions(-DDEBUG)
endif()

project(demo)

# 可执行程序的名字
set(APP_NAME_1 test1)
set(APP_NAME_2 test2)

# 添加子目录
add_subdirectory(calc)
add_subdirectory(sort)
add_subdirectory(test1)
add_subdirectory(test2)

add_subdirectory(src)
