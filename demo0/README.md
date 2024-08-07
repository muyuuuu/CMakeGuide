软件安装、环境配置的事我这里就略过了，网上有大把的教程，让我们直切主题。

---

用 `CMake` 的目的只有一个，我们不可能把所有的模块、函数的声明和定义放到一个文件中。

所以用 `CMake` 把工程目录组织一下，让所有的 `.h, .c, .cpp` 文件听指挥，让 `main` 函数能成功的运行起来。优点如下：

- 跨平台
- 能够管理大型项目
- 简化编译构建过程和编译过程，不用直接写欲仙欲死的 `Makefile`
- 可扩展：可以为 `cmake` 编写特定功能的模块，扩充 `cmake` 功能

此外，使用 `cmake` 命令时必须要有 `CMakeLists.txt` 文件。比如在 A 目录下：

```
A /
|-- CMakelists.txt
|-- main.cpp    
```

如果在 A 目录直接执行 `cmake` 命令，会在 A 目录下生成很多并不需要的辅助文件，目录看起来会很乱。所以我们一般在使用 `cmake` 命令时，会在 `main.cpp` 的同级目录下新建 `build` 文件夹，在 `build` 目录中完成编译。

```
A /
|-- build/ 
|-- CMakelists.txt
|-- main.cpp    
```

命令如下：

```
mkdir build
cd build
cmake ..
make
```

这样，编译的辅助文件、库、可执行文件都在 `build` 文件夹下，方便管理。
