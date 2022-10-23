#include "Life.h"


Life::Life(size_t vSize, size_t hSize, wchar_t symbol) :vSize_(vSize), hSize_(hSize), symbol_(symbol)
{
	SelectMemory();
	for (int i = 0; i < vSize_; i++)
	{
		for (int j = 0; j < hSize_; j++)
		{
			field_[i][j] = (rand() % 2 == 1) ? symbol_ : ' ';
		}
	}
}

Life::Life(size_t vSize, size_t hSize, wchar_t symbol, std::string filePath) :vSize_(vSize), hSize_(hSize), symbol_(symbol)
{
	SelectMemory();
	std::ifstream inputFile(filePath);
	char c;
	for (int i = 0; i < vSize_; i++)
	{
		for (int j = 0; j < hSize_; j++)
		{
			while (inputFile >> c && c == '\n') {}
			field_[i][j] = (c == '0') ? ' ' : symbol_;
		}
	}
	inputFile.close();
}


Life::~Life()
{
	for (int i = 0; i < vSize_; i++)
	{
		delete[] field_[i];
		delete[] field2_[i];
	}
	delete[] field_;
	delete[] field2_;
}

void Life::Print()
{
	for (int i = 0; i < vSize_; i++)
	{
		for (int j = 0; j < hSize_; j++)
		{
			std::wcout << field_[i][j];
		}
		std::wcout << std::endl;
	}
}

void Life::MakeStep()
{
	int countOfNeighbors;
	for (int i = 0; i < vSize_; i++)
	{
		for (int j = 0; j < hSize_; j++)
		{
			countOfNeighbors = CountNeighbors(i, j);
			if (field_[i][j] == ' ' && countOfNeighbors == 3)
			{ 
				field2_[i][j] = symbol_; 
			}
			else if (field_[i][j] == symbol_ && (countOfNeighbors > 3 || countOfNeighbors < 2))
			{
				field2_[i][j] = ' ';
			}
			else
			{
				field2_[i][j] = field_[i][j];
			}
		}
	}
	std::swap(field_, field2_);
}

void Life::SelectMemory()
{
	field_ = new wchar_t*[vSize_];
	field2_ = new wchar_t*[vSize_];
	for (int i = 0; i < vSize_; i++)
	{
		field_[i] = new wchar_t[hSize_];
		field2_[i] = new wchar_t[hSize_];
	}
}

bool Life::CanCount(int i, int j)
{
	return i >= 0 && i < vSize_ && j >= 0 && j < hSize_ && field_[i][j] == symbol_;
}

int Life::CountNeighbors(int i, int j)
{
	int result = 0;
	if (CanCount(i - 1, j - 1)) result++;
	if (CanCount(i - 1, j)) result++;
	if (CanCount(i - 1, j + 1)) result++;
	if (CanCount(i, j - 1)) result++;
	if (CanCount(i, j + 1)) result++;
	if (CanCount(i + 1, j - 1)) result++;
	if (CanCount(i + 1, j)) result++;
	if (CanCount(i + 1, j + 1)) result++;
	return result;
}
