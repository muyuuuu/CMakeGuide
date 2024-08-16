# 引用第三方库头文件
# target_include_directories(project PUBLIC ${CMAKE_SOURCE_DIR}/comm/inc)  
include_directories(${CMAKE_SOURCE_DIR}/comm/inc)  

# 将外部接口添加到目标中
set(PROJECT_INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
include_directories(${PROJECT_INC_DIR})

# 设置项目代码私有方法的目录，打包成库时，这些方法和接口不会暴露给外部
set(PROJECT_PRIV_DIR ${CMAKE_CURRENT_SOURCE_DIR}/priv)

# 定义一个添加新模块的方法
macro(add_module module)

# 模块自身的头文件视为私有方法，不对外暴露，添加到 PROJECT_PRIV_DIR 中
set(MODULE_INC "${CMAKE_CURRENT_SOURCE_DIR}/${module}/inc")
list(APPEND PROJECT_PRIV_DIR ${MODULE_INC})

# 搜索代码文件
set(MODULE_SRC "${CMAKE_CURRENT_SOURCE_DIR}/${module}/src")
aux_source_directory(${MODULE_SRC} ALL_MODULE_SRC)

endmacro(add_module)

# 实现新模块时，都添加到这里
# 比如 add_module(spatial)
add_module(calc)       # 添加计算相关的源代码
add_module(color)      # 添加颜色相关的源代码

# 设置出库路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)

# 制作动态库
add_library(project SHARED ${ALL_MODULE_SRC})
# 设置项目代码的头文件目录

# 指定 info 库的位置
find_library(INFO_LIBRARY info HINTS ${CMAKE_SOURCE_DIR}/comm/lib)  

# 私有形式添加私有头文件
message(STATUS "private include header file: ${PROJECT_PRIV_DIR}")
target_include_directories(project PRIVATE ${PROJECT_PRIV_DIR})

# 链接第三方库
target_link_libraries(project PRIVATE ${INFO_LIBRARY})
