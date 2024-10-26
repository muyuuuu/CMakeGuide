#include "test.h"
#include "module_1.h"
#include "module_2.h"

int TestCase() {
    Module1();
    Module2();
    std::cerr << "Test Case\n";
    return -1;
}