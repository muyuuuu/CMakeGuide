执行脚本：`bash run.sh` 即可完成编译和执行。

实际 `C/C++` 项目中会有很多的目录和源代码，在通过 `CMake` 管理项目的时候如果只使用一个 `CMakeLists.txt`，那么这个文件相对会比较复杂。有一种化繁为简的方式就是给每个源码目录都添加一个 `CMakeLists.txt` 文件，这样每个文件都不会太复杂，而且更灵活，更容易维护。

本次项目的目录结构如下：

```
demo7/
├── CMakeLists.txt
├── comm                         # 实际项目难免使用第三方库，以 demo4 制作的动态库为例
│   ├── inc                      # 第三方库的头文件
│   │   └── info.h
│   └── lib                      # 存放第三方库
│       └── libinfo.so
├── project                      # 实际项目
│   ├── CMakeLists.txt           # project 目录下的 CMakeLists.txt
│   ├── calc                     # 项目子模块 1，计算模块
│   │   ├── inc                  # 计算模块独有的头文件
│   │   │   └── calc.h
│   │   └── src                  # 计算模块的源代码，负责对外接口的具体实现
│   │       └── calc.cpp
│   ├── color                    # 项目子模块 2，颜色模块
│   │   ├── inc                  # 颜色模块独有的头文件
│   │   │   └── color.h
│   │   └── src                  # 颜色模块的源代码，负责对外接口的具体实现
│   │       └── color.cpp 
│   ├── inc                      # project 这个项目的对外接口
│   │   ├── ext.h
│   │   └── status.h
│   └── priv                     # project 项目的私有接口，外部无法使用，但 calc 和 color 可以使用
│       └── log.h
└── test                         # 测试模块
    ├── CMakeLists.txt           # 测试目录的 CMakeLists.txt
    ├── inc                      # 测试目录的头文件
    │   └── test.h
    └── src                      # 测试的源代码
        ├── main.cpp             # 入口程序
        ├── test_calc.cpp
        └── test_color.cpp
```

# 根节点的 CMakeLists.txt

```
cmake_minimum_required(VERSION 3.1)

project(my_project)

add_subdirectory(project)

add_subdirectory(test)
```

在 `CMake` 中，`add_subdirectory` 指令用于向构建添加子目录。这个子目录通常包含它自己的 `CMakeLists.txt` 文件和一些源代码。当 `add_subdirectory` 被调用时，`CMake` 会查找子目录中的 `CMakeLists.txt` 文件，并处理该文件以生成构建系统所需的目标、依赖关系和其他指令。

子目录可以访问根目录中定义的变量和目标，但 `CMake` 会为子目录创建一个新的作用域。这意味着在子目录中定义的变量和目标默认不会影响到父目录或其他子目录。

# project 的 CMakeLists.txt

```
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
```

1. 首先定义了一个函数 `add_module` 来添加新模块，由于各个模块的 `inc` 目录并不需要对外开放，因此添加到私有头文件 `PROJECT_PRIV_DIR` 中
2. 对于 `find_library(INFO_LIBRARY info HINTS ${CMAKE_SOURCE_DIR}/comm/lib)`
    1. `INFO_LIBRARY`：这是我们自己定义的变量名，如果 `find_library` 成功找到库，它将被设置为找到的库的完整路径。
    2. `info`：这是要查找的库的名称。`CMake` 将尝试查找名为 `libinfo.a, libinfo.so, info.lib` 等的库文件。
    3. `HINTS`：这个选项用于给 `find_library` 命令提供一组额外的目录，在这些位置中查找库文件，这可以加快搜索过程，也就是第四个参数。
    4. `${CMAKE_SOURCE_DIR}/comm/lib`：第三方库的存放路径。
3. `target_link_libraries(project PRIVATE ${INFO_LIBRARY})` 表示将 `${INFO_LIBRARY}` 链接给 `project`
    1. `PRIVATE`：库仅用于构建当前目标，不会传递给任何链接到当前目标的其他目标。可以确保库的依赖关系在构建系统中保持清晰和隔离，减少不必要的依赖传递。这有助于保持项目的可维护性和可理解性。
    2. `PUBLIC`：库用于构建当前目标，并且还会传递给任何链接到当前目标的其他目标。
    3. `INTERFACE`：库不用于构建当前目标，但会传递给任何链接到当前目标的其他目标。这通常用于指定一个库为其消费者提供哪些接口库
4. `target_include_directories(project PUBLIC ${PROJECT_INC_DIR})` 和前者大体相同，为目标 `project` 添加头文件。`include_directories` 是全局的，而 `target_include_directories` 是目标特定的。在现代 `CMake` 中，推荐使用 `target_include_directories` 来管理头文件搜索路径，因为它提供了更好的隔离性和依赖关系管理。
    1. `PRIVATE`：指定的头文件目录仅对当前目标可见。换句话说，只有当前目标能够访问这些头文件，而其他链接到当前目标的目标则无法访问。这通常用于那些只应由当前目标内部使用的头文件。
    2. `PUBLIC`：指定的头文件目录对当前目标以及所有链接到当前目标的其他目标都可见。这意味着不仅当前目标可以使用这些头文件，而且任何链接到当前目标的其他目标也可以使用它们。这通常用于那些既由当前目标使用又被其他目标共享的头文件。
    3. `INTERFACE`：指定的头文件目录对当前目标不可见，但对所有链接到当前目标的其他目标可见。这意味着当前目标不能使用这些头文件（如果需要，应使用其他方式包含），但任何链接到当前目标的其他目标都可以使用它们。这通常用于那些仅由其他目标使用的头文件，而不是由当前目标直接使用。

# 测试模块的 CMakeLists.txt

注意：可执行文件是在 `test` 模块下生成的。

```
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

# 设置可执行文件的目录
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)

# test 需要使用的文件
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

# 测试 project 时，需要访问对外的接口函数
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/../project/inc)

# 可执行文件
add_executable(test_project ${SRC_LIST})
target_link_libraries(test_project PRIVATE project)
```

最终执行结果输出如下：

```
=============== summary report ===================
UNIT_TEST/home/muyu/Desktop/cmake_learn/demo7/test/src/test_calc.cpp:6::calling GRTZERO == multiply(2, 3)
this is info1
[Multiply] [/home/muyu/Desktop/cmake_learn/demo7/project/calc/src/calc.cpp multiply 24] result is 0UNIT_TEST/home/muyu/Desktop/cmake_learn/demo7/test/src/test_calc.cpp:6::error 
UNIT_TEST/home/muyu/Desktop/cmake_learn/demo7/test/src/test_calc.cpp:7::calling LEQZERO == multiply(4, -1)
this is info1
[Multiply] [/home/muyu/Desktop/cmake_learn/demo7/project/calc/src/calc.cpp multiply 24] result is 0UNIT_TEST/home/muyu/Desktop/cmake_learn/demo7/test/src/test_calc.cpp:7::passed 
UNIT_TEST/home/muyu/Desktop/cmake_learn/demo7/test/src/test_calc.cpp:8::calling LEQZERO == multiply(0, -1)
this is info1
[Multiply] [/home/muyu/Desktop/cmake_learn/demo7/project/calc/src/calc.cpp multiply 24] result is 0UNIT_TEST/home/muyu/Desktop/cmake_learn/demo7/test/src/test_calc.cpp:8::passed 
=============== Case: 1 TEST Passed ===================
UNIT_TEST/home/muyu/Desktop/cmake_learn/demo7/test/src/test_color.cpp:6::calling INVALID == ShowRGB(-1, 2, 3)
UNIT_TEST/home/muyu/Desktop/cmake_learn/demo7/test/src/test_color.cpp:6::passed 
UNIT_TEST/home/muyu/Desktop/cmake_learn/demo7/test/src/test_color.cpp:7::calling INVALID == ShowRGB(4, -1, 9)
UNIT_TEST/home/muyu/Desktop/cmake_learn/demo7/test/src/test_color.cpp:7::passed 
UNIT_TEST/home/muyu/Desktop/cmake_learn/demo7/test/src/test_color.cpp:8::calling SUCCESS == ShowRGB(1, 1, 1)
[ShowRGB] [/home/muyu/Desktop/cmake_learn/demo7/project/color/src/color.cpp ShowRGB 14] R is 1
[ShowRGB] [/home/muyu/Desktop/cmake_learn/demo7/project/color/src/color.cpp ShowRGB 15] G is 1
[ShowRGB] [/home/muyu/Desktop/cmake_learn/demo7/project/color/src/color.cpp ShowRGB 16] B is 1
this is info2
UNIT_TEST/home/muyu/Desktop/cmake_learn/demo7/test/src/test_color.cpp:8::passed 
=============== Case: 2 TEST Passed ===================
=============== total: 2 ===================
=============== pass : 2 ===================
=============== fail: 0 ===================
```