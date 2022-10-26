#define CTEST_MAIN
#include <ctest.h>
#include <iostream>

int main(int argc, const char** argv)
{
    setlocale(LC_ALL, "");
    return ctest_main(argc, argv);
}