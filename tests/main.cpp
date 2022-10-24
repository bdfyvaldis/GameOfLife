#define CTEST_MAIN
#include "../third-party/ctest/ctest.h"
#include <iostream>

int main(int argc, const char** argv)
{
    setlocale(LC_ALL, "");
    return ctest_main(argc, argv);
}