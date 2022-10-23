#pragma once
#include <iostream>
#include <string>
#include <fstream>

class Life
{
public:

	Life(size_t vSize, size_t hSize, wchar_t symbol);
	Life(size_t vSize, size_t hSize, wchar_t symbol, std::string filePath);
	~Life();
	void Print();
	void MakeStep();

private:

	wchar_t** field_;
	wchar_t** field2_;
	size_t vSize_; 
	size_t hSize_;
	wchar_t symbol_;

	void SelectMemory();
	
	bool CanCount(int i, int j);
	int CountNeighbors(int i, int j);
};

