#include <Life.h>
#include <cstring>
#include <ctest.h>
#include <iostream>
#include <sstream>

CTEST(TestGame, testNoFile)
{
    bool result = false;
    try {
        Life life(L"tests/nofile.txt");
    } catch (std::runtime_error e) {
        if (strcmp(e.what(), "Can't open preset-file") == 0)
            result = true;
    }
    ASSERT_TRUE(result);
}

CTEST(TestGame, testEmptyfile)
{
    bool result = false;
    try {
        Life life(L"tests/not_enough_data.txt");
    } catch (std::runtime_error e) {
        if (strcmp(e.what(),
                   "Incorrect structure of the input file. Check input file!")
            == 0)
            result = true;
    }
    ASSERT_TRUE(result);
}

CTEST(TestGame, testPrint)
{
    Life life(L"tests/simple.txt");
    std::wstringstream sstr;
    life.Print(sstr);
    std::wstring str = sstr.str();
    std::wstring str1 = L"00000\n00100\n00100\n00100\n00000\n";
    ASSERT_WSTR(str.c_str(), str1.c_str());
}

CTEST(TestGame, testMakeStep)
{
    Life life(L"tests/simple.txt");
    std::wstringstream sstr;
    life.MakeStep();
    life.Print(sstr);
    std::wstring str = sstr.str();
    std::wstring str1 = L"00000\n00000\n01110\n00000\n00000\n";
    ASSERT_WSTR(str.c_str(), str1.c_str());
}

CTEST(TestGame, testMakeStepBorderPoints)
{
    Life life(L"tests/border.txt");
    std::wstringstream sstr;
    life.MakeStep();
    life.Print(sstr);
    std::wstring str = sstr.str();
    std::wstring str1 = L"00000\n00000\n00000\n00000\n00000\n";
    ASSERT_WSTR(str.c_str(), str1.c_str());
}