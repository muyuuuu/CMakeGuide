cmake_minimum_required(VERSION 3.0)

project(HelloWorld)

# 包含头文件路径
include_directories(${PROJECT_SOURCE_DIR}/inc)

# 包含静态库路径
# link_directories(${PROJECT_SOURCE_DIR}/lib)

# 链接静态库
# link_libraries(libinfo.a)

# 指定要链接的动态库的路径
link_directories(${PROJECT_SOURCE_DIR}/lib)

add_executable(main main.cpp)

target_link_libraries(main libinfo.so)
