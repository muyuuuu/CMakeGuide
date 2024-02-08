```
mkdir build
cd build
cmake ..
make
./main
```

在上面的例子中一共提供了 3 个源代码文件，假设这 3 个源代码文件需要反复被使用，每次都直接将它们的名字写出来确实是很麻烦。如果有 100 个，1000 个源文件呢？？？

此时我们就需要定义一个变量，将文件名对应的字符串存储起来，即：`set(CODE_LIST info1.cpp info2.cpp info3.cpp main.cpp)`。