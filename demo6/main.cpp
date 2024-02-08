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