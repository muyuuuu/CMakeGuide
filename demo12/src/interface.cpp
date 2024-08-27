#include "interface.h"
#include "module_1.h"
#include "module_2.h"

void __Interface() {
  std::cout << " hei hei " << std::endl;
  Module1();
  Module2();
}

void Interface() { __Interface(); }