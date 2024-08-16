#include "test.h"

#define TEST_TABLE                       \
    X_MACROS(TEST_CALC,  test_calc)       \
    X_MACROS(TEST_COLOR, test_show_rgb)      \

/*定义命令列表*/
typedef enum
{
    TEST_START,
    #define X_MACROS(a, b) a,
    TEST_TABLE
    #undef X_MACROS
    TEST_END
} cmd_e;

/*定义字符串列表用作Log打印*/
const char* cmd_str[] =
{
    #define X_MACROS(a, b) #a,
    TEST_TABLE
    #undef X_MACROS
};

typedef int (*func)(void);

const func func_table[] =
{
    #define X_MACROS(a, b) b,
    TEST_TABLE
    #undef X_MACROS
};

static int cmd_handle(int cmd)
{
    if (cmd < TEST_END)
    {
        return func_table[cmd]();
    }
    return -1;
}

int main()
{
    printf("=============== summary report ===================\n");
    int total = TEST_END - 1;
    int passed = 0;

    for (int i = TEST_START; i < TEST_END; i++)
    {
        if ((i > TEST_START) && (i < TEST_END))
        {
            if (0 == cmd_handle(i - 1))
            {
                passed++;
                printf("=============== Case: %d TEST Passed ===================\n", i);
            }
            else
            {
                printf("=============== Case: %d TEST Falied ===================", i);
            }
        }
    }
    printf("=============== total: %d ===================\n", total);
    printf("=============== pass : %d ===================\n", passed);
    printf("=============== fail: %d ===================\n", total - passed);

    return 0;
}