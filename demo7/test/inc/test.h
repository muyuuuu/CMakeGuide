#ifndef __test_h__
#define __test_h__

#ifdef __cpluscplus
extern "C"
{
#endif

#include "ext.h"
#include "log.h"

#include <stdio.h>

#define __TO_STR__(x) #x ":"
#define __TO_REAL__(x) __TO_STR__(x)
// 文件:行号
#define __FILE_LINE__ __FILE__ ":" __TO_REAL__(__LINE__)

#define UNIT_TEST(exper, res) \
    do { \
        LOG("UNIT_TEST", __FILE_LINE__ ":calling " #exper "\n"); \
        if (0 == (exper)) { \
            LOG("UNIT_TEST", __FILE_LINE__ ":error \n"); \
            res = -1; \
        } else { \
            res = 0; \
            LOG("UNIT_TEST", __FILE_LINE__ ":passed \n"); \
        } \
    } while(0)

int test_calc();
int test_show_rgb();

#ifdef __cpluscplus
}
#endif

#endif