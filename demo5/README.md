在 `demo4` 中，我们制作了静态链接库和动态链接库，那么在 `demo5` 中，我们就来加载一下。目录结构：

```
├── CMakeLists.txt
├── inc
│   └── info.h
├── lib
│   ├── libinfo.a
│   └── libinfo.so
├── main.cpp
└── README.md
```

加载外部库其实是很常见的场景：一个公司写完一些算法模块后，由于不想让别人看到源代码，所以把代码打包成库，并提供函数声明的头文件，告诉用户怎么使用即可。

使用静态库的方法为：

```
include_directories(${PROJECT_SOURCE_DIR}/inc)  # 包含头文件
link_directories(${PROJECT_SOURCE_DIR}/lib)     # 包含静态库路径
link_libraries(libinfo.a)                       # 链接静态库
add_executable(main main.cpp)                   # 生成可执行文件
```

使用静态库的方法为：

```

include_directories(${PROJECT_SOURCE_DIR}/inc) # 包含头文件路径
link_directories(${PROJECT_SOURCE_DIR}/lib)    # 包含动态库路径
add_executable(main main.cpp)                  # 生成可执行文件
target_link_libraries(main libinfo.so)         # 链接动态库
```

可以看到两者的区别是：

- 静态链接：先链接库，在生成可执行文件
- 动态链接：先生成可执行文件，在链接库

这是因为静态库会在生成可执行程序的链接阶段被打包到可执行程序中，所以可执行程序启动时，静态库就已经被加载到内存中了。而动态库不会在链接阶段被打包到可执行文件中，当可执行程序被启动并且调用了动态库中的函数的时候，动态库才会被加载到内存。因此，在 `cmake` 中指定要链接的动态库的时候，应该将链接命令写到生成可执行文件之后。

此外：动态库的链接具有传递性，如果动态库 A 链接了动态库B、C，动态库D链接了动态库A，此时动态库D相当于也链接了动态库B、C，并可以使用动态库B、C中定义的方法。