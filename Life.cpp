#include "Life.h"

Life::Life(size_t vSize, size_t hSize, wchar_t symbol, wchar_t whitespace)
    : height_(vSize), width_(hSize), symbol_(symbol), whitespace_(whitespace)
{
    AllocateMemory();
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            field_[i][j] = (rand() % 2 == 1) ? symbol_ : whitespace_;
        }
    }
}

Life::Life(std::wstring file_path)
{
    std::string ulul(file_path.begin(), file_path.end());
    std::ifstream input_file(ulul);
    if (!input_file) {
        throw std::runtime_error("Can't open preset-file");
    }
    input_file >> height_;
    input_file >> width_;
    if (height_ <= 0 || height_ > MAX_SIZE || width_ <= 0
        || width_ > MAX_SIZE) {
        throw std::runtime_error(
                "Incorrect structure of the input file. Check input file!");
    }
    AllocateMemory();
    int code_of_symbol;
    input_file >> code_of_symbol;
    symbol_ = static_cast<wchar_t>(code_of_symbol);
    input_file >> code_of_symbol;
    whitespace_ = static_cast<wchar_t>(code_of_symbol);
    char c;
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            while (input_file >> c && c == '\n') {
            }
            field_[i][j] = (c == '0') ? whitespace_ : symbol_;
        }
    }
    input_file.close();
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
    int count_of_neighbors;
    for (int i = 0; i < height_; i++) {
        for (int j = 0; j < width_; j++) {
            count_of_neighbors = CountNeighbors(i, j);
            if (field_[i][j] == whitespace_ && count_of_neighbors == 3) {
                field2_[i][j] = symbol_;
            } else if (
                    field_[i][j] == symbol_
                    && (count_of_neighbors > 3 || count_of_neighbors < 2)) {
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

void Life::Save(std:: string filepath)
{

}