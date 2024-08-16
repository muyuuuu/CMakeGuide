在某些特殊场景下，不同文件夹下可能会有同名的文件。如下所示：

```
include/
|---- test/
     |---- log.h
|---- calc/
     |---- log.h
```

极端情况下，`test` 和 `calc` 文件夹下都有 `log.h` 这个文件，不过一个用来打印测试信息，一个用来打印计算信息。

那么在 `main.cpp` 中，我们就需要：

```cpp
#include <test/log.h>
#include <calc/log.h>
```

避免冲突。幸运的是，我们按照 `demo3` 中的 `CMakeLists.txt` 写法并不会翻车：

```cmake
cmake_minimum_required(VERSION 3.0)

project(HelloWorld)

message(STATUS "======= ${PROJECT_SOURCE_DIR}")
# 头文件
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(main  main.cpp)
```

因为 `include_directories(${PROJECT_SOURCE_DIR}/include)` 是添加 `include` 下的头文件，也就是添加的是 `test/log.h` 和 `calc/log.h`，所以在 `main.cpp` 中必须：

```cpp
#include <test/log.h>
#include <calc/log.h>
```

下面的写法会报错：

```cpp
#include <log.h>
#include <log.h>
```

那么问题来了，对于下面的目录：

```
include/
|---- test/
     |---- test.h
|---- calc/
     |---- calc.h
```

如果我想在 `main.cpp` 中直接引用，而不用必须指定路径，该怎么办呢？

```cpp
#include <test.h>
#include <calc.h>
```

想必聪明的你想到了，修改 `CMakeLists.txt`，包含的头文件的目录不能只指定到 `include/`，而是 `include/test` 和 `include/calc`。

除了手动添加外，这里我们给出一个函数去递归的搜索 `include` 目录下的头文件并添加：

```makefile
file(GLOB_RECURSE HEADER_FILES "${PROJECT_SOURCE_DIR}/include/*.h")     # 递归的搜索目录下的 h 文件，添加到 HEADER_FILES
foreach(header ${HEADER_FILES})                                         # 编译 HEADER_FILES，添加头文件，dir 的目录是 include/calc, include/test
  get_filename_component(dir ${header} PATH)
    message(STATUS "======= ${dir}")
  list(APPEND MY_INCLUDE_DIRS ${dir})
endforeach()

list(REMOVE_DUPLICATES MY_INCLUDE_DIRS)                                 # 去重
include_directories(${MY_INCLUDE_DIRS})                                 # 添加头文件
```