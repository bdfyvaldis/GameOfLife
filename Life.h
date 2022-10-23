#pragma once
#include <iostream>
#include <string>
#include <fstream>

class Life
{
public:

	Life(size_t vSize, size_t hSize, wchar_t symbol);
	Life(std::string filePath);
	~Life();
	void Print(std::wostream& stream=std::wcout);
	void MakeStep();

private:

	wchar_t** field_;
	wchar_t** field2_;
	size_t height_; 
	size_t width_;
	wchar_t symbol_;
	wchar_t whitespace_;

	void SelectMemory();
	
	bool CanCount(int i, int j);
	int CountNeighbors(int i, int j);
};

