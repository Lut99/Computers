#include <iostream>

#include "test_compilation.h"

using namespace Test;

TestClass::TestClass(char *hello_world)
    :hello_world(hello_world)
{}

void TestClass::print() {
    std::cout << this->hello_world << std::endl;
}