#include "../third-party/ctest/ctest.h"

#include "../Life.h"
#include <iostream>
#include <sstream>

CTEST(TestGame, testPrint)
{
    Life life("tests/simple.txt");
    std::wstringstream sstr;
    life.Print(sstr);
    std::wstring str = sstr.str();
    std::wstring str1 = L"00000\n00100\n00100\n00100\n00000\n";
    ASSERT_WSTR(str.c_str(), str1.c_str());
}

CTEST(TestGame, testMakeStep)
{
    Life life("tests/simple.txt");
    std::wstringstream sstr;
    life.MakeStep();
    life.Print(sstr);
    std::wstring str = sstr.str();
    std::wstring str1 = L"00000\n00000\n01110\n00000\n00000\n";
    ASSERT_WSTR(str.c_str(), str1.c_str());
}

CTEST(TestGame, testMakeStepBorderPoints)
{
    Life life("tests/border.txt");
    std::wstringstream sstr;
    life.MakeStep();
    life.Print(sstr);
    std::wstring str = sstr.str();
    std::wstring str1 = L"00000\n00000\n00000\n00000\n00000\n";
    ASSERT_WSTR(str.c_str(), str1.c_str());
}