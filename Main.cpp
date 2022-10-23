#include<iostream>
#include<cstdio>
#include<termios.h>
#include<unistd.h>
#include"Life.h"

int mygetch()
{
	struct termios oldt, newt;
	int ch;
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	ch=getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return ch;
}



int main()
{
	setlocale(LC_ALL, "");
	Life life(20, 100, 9994); //9610
	for (;;)
	{
		system("clear");
		std::wcout << "Press any key to see new generation. \'q\' - for exit" << std::endl;
		life.MakeStep();
		life.Print();
		if (mygetch()=='q') break;
	}
	system("clear");

}




