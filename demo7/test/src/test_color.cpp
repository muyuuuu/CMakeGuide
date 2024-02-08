#include "test.h"

int test_show_rgb()
{
    int res = 0;
    UNIT_TEST(INVALID == ShowRGB(-1, 2, 3), res);
    UNIT_TEST(INVALID == ShowRGB(4, -1, 9), res);
    UNIT_TEST(SUCCESS == ShowRGB(1, 1, 1), res);
    return res;
}