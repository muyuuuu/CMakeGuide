#include "test.h"

int test_calc()
{
    int res = 0;
    UNIT_TEST(GRTZERO == multiply(2, 3), res);
    UNIT_TEST(LEQZERO == multiply(4, -1), res);
    UNIT_TEST(LEQZERO == multiply(0, -1), res);
    return res;
}