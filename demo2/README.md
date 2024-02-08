```
mkdir build
cd build
cmake ..
make
./main
```

在这个例子中一共提供了 3 个源代码文件，假设这 3 个源代码文件需要反复被使用，每次都在 `CMakelists.txt` 中将它们的名字写出来很麻烦。如果有 100 个，1000 个源文件呢？？？不可能手写的。

此时我们就需要定义一个变量，将对应的源文件们存储到这个变量中。即：`set(CODE_LIST info1.cpp info2.cpp info3.cpp main.cpp)`，表示将 `main.cpp, info1.cpp, info2.cpp, info3.cpp` 存储到 `CODE_LIST` 中。