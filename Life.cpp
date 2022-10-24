#include "Life.h"

Life::Life(size_t vSize, size_t hSize, wchar_t symbol, wchar_t whitespace)
    : height_(vSize), width_(hSize), symbol_(symbol), whitespace_(whitespace)
{
    AllocateMemory();
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            field_[i][j] = (rand() % 2 == 1) ? symbol_ : ' ';
        }
    }
}

Life::Life(std::string filePath)
{
    std::ifstream inputFile(filePath);
    inputFile >> height_;
    inputFile >> width_;
    AllocateMemory();
    int code_of_symbol;
    inputFile >> code_of_symbol;
    symbol_ = static_cast<wchar_t>(code_of_symbol);
    inputFile >> code_of_symbol;
    whitespace_ = static_cast<wchar_t>(code_of_symbol);
    char c;
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            while (inputFile >> c && c == '\n') {
            }
            field_[i][j] = (c == '0') ? whitespace_ : symbol_;
        }
    }
    inputFile.close();
}

Life::~Life()
{
    for (int i = 0; i < height_; i++) {
        delete[] field_[i];
        delete[] field2_[i];
    }
    delete[] field_;
    delete[] field2_;
}

void Life::Print(std::wostream& stream)
{
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            stream << field_[i][j];
        }
        stream << std::endl;
    }
}

void Life::MakeStep()
{
    int countOfNeighbors;
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            countOfNeighbors = CountNeighbors(i, j);
            if (field_[i][j] == whitespace_ && countOfNeighbors == 3) {
                field2_[i][j] = symbol_;
            } else if (
                    field_[i][j] == symbol_
                    && (countOfNeighbors > 3 || countOfNeighbors < 2)) {
                field2_[i][j] = whitespace_;
            } else {
                field2_[i][j] = field_[i][j];
            }
        }
    }
    std::swap(field_, field2_);
}

void Life::AllocateMemory()
{
    field_ = new wchar_t*[height_];
    field2_ = new wchar_t*[height_];
    for (int i = 0; i < height_; i++) {
        field_[i] = new wchar_t[width_];
        field2_[i] = new wchar_t[width_];
    }
}

bool Life::CanCount(int i, int j)
{
    return i >= 0 && i < height_ && j >= 0 && j < width_
            && field_[i][j] == symbol_;
}

int Life::CountNeighbors(int i, int j)
{
    int result = 0;
    if (CanCount(i - 1, j - 1))
        result++;
    if (CanCount(i - 1, j))
        result++;
    if (CanCount(i - 1, j + 1))
        result++;
    if (CanCount(i, j - 1))
        result++;
    if (CanCount(i, j + 1))
        result++;
    if (CanCount(i + 1, j - 1))
        result++;
    if (CanCount(i + 1, j))
        result++;
    if (CanCount(i + 1, j + 1))
        result++;
    return result;
}
