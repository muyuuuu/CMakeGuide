`demo4` 会生成动/静态链接库，我们想把头文件和动静态链接库一键导出供用户使用，而不是手动拷贝和粘贴。

基于 `demo4` 的例子，我们修改一下，此时只需要在 `CMakeLists.txt` 中添加几行代码即可：

```makefile
set(EXPORT_DIR ${CMAKE_BINARY_DIR}/export)                                # 设置导出路径
install(TARGETS info LIBRARY DESTINATION ${EXPORT_DIR})                   # 导出 info 库到 build/export
install(DIRECTORY ${PROJECT_SOURCE_DIR}/inc DESTINATION ${EXPORT_DIR}/)   # 将头文件导出到 build/export/
```

不过这里要执行 `make install` 而不是 `make`：

- make 用于编译源代码，而 make install 用于将编译好的软件安装到系统中。
- make 自动化编译过程，make install 自动化安装过程。

