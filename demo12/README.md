跨目录引用头文件和代码文件是很常见的事情。比如对于以下的目录结构：

1. 需要在 `include` 和 `src` 的代码中用一用 `module1` 和 `module2` 中的函数、类、变量等等，生成动态库和可执行文件。
2. 同样在 `test` 目录下的 `test.cpp` 中用一用 `module1` 和 `module2` 中的函数、类、变量，并生成可执行文件。
3. 在 `online` 目录中的 `online.cpp` 中也要用一用 `module1` 和 `module2` 中的函数、类、变量，并生成可执行文件。

```
├── main.cpp
├── CMakeLists.txt
├── include
│   └── interface.h
│── src
│   └── interface.cpp
│── test
│   ├── CMakeLists.txt
│   └── test.cpp
│── online
│   ├── CMakeLists.txt
│   └── online.cpp
├── modules
│   ├── CMakeLists.txt
│   ├── module1
│   │   ├── include
│   │   │   └── module_1.h
│   │   └── src
│   │       └── module_1.cpp
│   └── module2
│       ├── include
│       │   └── module_2.h
│       └── src
│           └── module_2.cpp
```

如果在根目录、`test` 目录、`online` 目录下的 `CMakeLists.txt` 中强行使用 `include_directories` 指定 `modules/module1/include`，需要将这种代码重复三次，不够优雅。

一种合适的方式是在 `modules` 的 `CMakeLists.txt` 中定义**全局变量**：

```
set_property(GLOBAL PROPERTY MODULE_INC_DIRS ${MODULE_INC_DIRS})
set_property(GLOBAL PROPERTY MODULE_LIB_SRCS ${MODULE_LIB_SRCS})
```

并将 `modules` 下的头文件放到全局变量 `MODULE_INC_DIRS` 中，将 `modules` 下的源代码文件放到全局变量 `MODULE_LIB_SRCS` 中，统一对外提供出去。如果外部需要使用，只需要获取这个全局变量即可。

---

以根目录为例，获取这个全局变量：

```
get_property(MODULE_INC_DIRS GLOBAL PROPERTY  "MODULE_INC_DIRS")
get_property(MODULE_LIB_SRCS GLOBAL PROPERTY  "MODULE_LIB_SRCS")
```

将根目录的头文件 `interface.h` 和 `MODULE_INC_DIRS` 放到一起并 `include_directories`，就可以制作可执行文件和动态库啦：

```
set(ALGO_INC_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")  # 指定根目录头文件
list(APPEND ALGO_INC_DIRS "${MODULE_INC_DIRS}")           # 追加 modules 的头文件
include_directories(${ALGO_INC_DIRS})                     # 包含全部头文件
```
