#include "Menu.h"

void Menu::Print(std::wostream& stream)
{
    stream << L"\033[;30m\033[0;47m\033[1m <space> \033[0m - new generation"
           << std::endl;
}