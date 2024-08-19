在写 C 程序时我们需要注意：任何潜在的编译 warning 都会导致潜在的 bug；即使编译没有任何 warning 和 error，也可能存在运行期 bug。为了使程序更加稳定，我们可以对 cmake 进行如下设置：

```makefile
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
```

- -Wall 和 -Wextra 这两个选项启用了几乎所有的编译时警告信息。
-Werror：这个选项将警告信息视为错误。当编译器发出警告时，如果启用了-Werror，则编译过程会停止。有助于确保开发者不会忽略任何警告信息。

对于 main.cpp，就会发生如下错误：

```
error: ‘a’ is used uninitialized in this function [-Werror=uninitialized]
    5 |     std::cerr << a << std::endl;
```

使用了变量 `a`，但我们没有赋初值。是的，看似没有问题的代码，却无法编译通过。

假如我们在维护一个几十万行的大项目，发生了一个莫名其妙的 bug。我们费劲千辛万苦，在几百个文件几千个函数里面，找到了以下代码：

```c
int sum;
for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 10; j++) {
        sum += arr[i][j];
    }
}
return sum;
```

- 你能看出来问题在哪吗？
- 如果开启上述选项，是不是可以更快的定位？