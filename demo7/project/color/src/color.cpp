#include <iostream>
#include "color.h"

int ShowRGB(int R, int G, int B)
{
    if ((R < 0) || (G < 0) || (B < 0))
    {
        return INVALID;
    }
    if ((R > 255) || (G > 255) || (B > 255))
    {
        return INVALID;
    }
    LOG("ShowRGB", "R is %d\n", R);
    LOG("ShowRGB", "G is %d\n", G);
    LOG("ShowRGB", "B is %d\n", B);
    ShowInfo2();
    return SUCCESS;
}