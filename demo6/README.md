```
mkdir build
cd build
cmake ..
make
./install/main
```

这个主要得结合代码来看：

```C++
#include <iostream>

int main()
{
#ifdef TEST
    std::cout << "cond 1" << std::endl;
#else
    std::cout << "cond 2" << std::endl;
#endif
    return 0;
}
```

代码不难理解，如果定义了 `TEST` 这个宏，输出 `cond 1`，否则输出 `cond 2`。`TEST` 这个宏可以在 `CMakeLists.txt` 这个文件中定义：

```
add_definitions(-DTEST)
```

这种方式一般用于跨平台的处理。如果代码在 `windows` 平台运行，那么加载 `windows` 平台的库；如果在 `linux` 平台运行，那么加载 `linux` 平台的库。如下所示：

```C++
#ifdef WINDOWS
    #include "windows.h"
#else
    #include "linux.h
```