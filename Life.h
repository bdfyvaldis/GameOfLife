#pragma once
#include <fstream>
#include <iostream>
#include <string>

class Life {
public:
    Life(size_t vSize, size_t hSize, wchar_t symbol, wchar_t whitespace);
    Life(std::string filePath);
    ~Life();
    void Print(std::wostream& stream = std::wcout);
    void MakeStep();

private:
    static const int MAX_SIZE = 100; 
    wchar_t** field_;
    wchar_t** field2_;
    size_t height_;
    size_t width_;
    wchar_t symbol_;
    wchar_t whitespace_;

    void AllocateMemory();

    bool CanCount(int i, int j);
    int CountNeighbors(int i, int j);
};
