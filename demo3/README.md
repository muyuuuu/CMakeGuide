```
├── CMakeLists.txt
├── inc
│   └── info.h
├── main.cpp
├── README.md
└── src
    ├── info1.cpp
    ├── info2.cpp
    └── info3.cpp
```

这是一个简单的工程目录，头文件位于 `inc` 目录下，实现的源代码位于 `src` 目录下。`main.cpp` 和 `CMakeLists.txt` 位于外部。

我们通过 `cmake` 内置的指令 `include_directories` 来加载头文件，使用 `aux_source_directory` 来搜索源代码文件：

```c
# 头文件
include_directories(${PROJECT_SOURCE_DIR}/inc)

# 源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)
```

也许你会好奇：`${PROJECT_SOURCE_DIR}` 和 `${CMAKE_CURRENT_SOURCE_DIR}` 是什么，之前没定义呀。这两个是 `cmake` 内置的变量，就像 C 语言中内置的 `__FILE__` 一样。

- `PROJECT_SOURCE_DIR` 表示工程的根目录
- `CMAKE_CURRENT_SOURCE_DIR` 表示当前处理的 `CMakeLists.txt` 所在的路径

用多了自然会熟练。说实话，什么根目录、当前目录、项目目录，`CMakeLists.txt` 所在目录都是很模糊的描述，如果不确定具体是哪个目录的话，我的建议是使用 `message` 函数来打印看看：

```
message(STATUS, "======= ${PROJECT_SOURCE_DIR}")
message(STATUS, "======= ${CMAKE_CURRENT_SOURCE_DIR}")
```

输出如下：

```
STATUS,======= /home/muyu/Desktop/cmake_learn/demo3
STATUS,======= /home/muyu/Desktop/cmake_learn/demo3
```

补充一些常用的内置变量：

```
PROJECT_SOURCE_DIR	        使用 cmake 命令后紧跟的目录，一般是工程的根目录
PROJECT_BINARY_DIR	        执行 cmake 命令的目录
CMAKE_CURRENT_SOURCE_DIR	当前处理的 CMakeLists.txt 所在的路径
CMAKE_CURRENT_BINARY_DIR	target 编译目录
EXECUTABLE_OUTPUT_PATH	    重新定义目标二进制可执行文件的存放位置
LIBRARY_OUTPUT_PATH	        重新定义目标链接库文件的存放位置
PROJECT_NAME	            返回通过 PROJECT 指令定义的项目名称
CMAKE_BINARY_DIR	        项目实际构建路径，假设在 build 目录进行的构建，那么得到的就是这个目录的路径
```