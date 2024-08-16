#include <iostream>
#include "calc.h"

static int add(int a, int b)
{
    return a + b;
}

int multiply(int a, int b)
{
    ShowInfo1();
    int flag = 1;
    if (b < 0)
    {
        flag = -1;
        b = -b;
    }
    int sum = 0;
    for (int i = 0; i < b; i++)
    {
        add(sum, a);
    }
    int res = sum * flag;
    LOG("Multiply", "result is %d", res);
    if (res <= 0)
    {
        return LEQZERO;
    }
    return GRTZERO;
}