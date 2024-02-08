```
mkdir build
cd build
cmake ..
make
```

学过操作系统或者 C 语言，一定对静态链接库(`.a, .lib`)、动态链接库(`.so, .dll`)不陌生。可惜我当时是纯 `python` 程序员，学操作系统的时候确实是云里雾里，不过没关系，我们今天来解密一下。

基于 `demo3` 的项目，我们将 `ShowInfo()` 这一系列函数封装成动态或者静态链接库，注意，一次编译只能生成一种库。

```
# 源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

# 制作静态库
# add_library(info STATIC ${SRC_LIST})

# 制作动态库
add_library(info SHARED ${SRC_LIST})
```

制作库时只有 `STATIC` 和 `SHARED` 的区别。至于动态链接库和静态链接库的本质区别，emmmm，是操作系统的经典内容，但说起来有点复杂，和本仓库也关系不大，所以网上自己搜一搜吧。

之后在设置生成的库放到 `build/lib` 目录下：

```
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/lib)
```

注意，在 `CMakelists.txt` 文件中，本次编译并没有生成可执行文件。