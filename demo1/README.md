# 编译执行

```
mkdir build
cd build
cmake ..
make
./main
```

# 解析

- `cmake_minimum_required`：指定使用的 `CMake` 的最低版本，这里我们指定为 3.0
- `project`：定义工程名称

上述两个指令是建议写上的，比如避免 `CMake` 版本落后导致的编译错误。不写不会报错，但是会有警告。

- `add_executable`：将参数中的源代码文件 `main.cpp` 和 `info.cpp` 编译、链接生成可执行文件 `main`。

打开 `build` 文件夹，执行执行 `./main` 即可。