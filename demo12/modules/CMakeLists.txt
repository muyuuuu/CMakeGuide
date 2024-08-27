macro(add_module name)
    set(MODULE_INC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${name}/include")
    list(APPEND MODULE_INC_DIRS ${MODULE_INC_DIR})

    aux_source_directory("${CMAKE_CURRENT_SOURCE_DIR}/${name}/src" MODULE_LIB_SRCS)
endmacro()

add_module(module1)     # 添加两个模块
add_module(module2)

set_property(GLOBAL PROPERTY MODULE_INC_DIRS ${MODULE_INC_DIRS})   # 设置全局变量
set_property(GLOBAL PROPERTY MODULE_LIB_SRCS ${MODULE_LIB_SRCS})
