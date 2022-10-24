#include "Life.h"
#include <cstdio>
#include <iostream>
#include <termios.h>
#include <unistd.h>

int my_getch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int main()
{
    setlocale(LC_ALL, "");
    // Life life(20, 100, 9994); //9610
    Life life("presets//gun.txt");
    for (;;) {
        system("clear");
        std::wcout << "Press any key to see new generation. \'q\' - for exit"
                   << std::endl;
        life.Print();
        life.MakeStep();
        if (my_getch() == 'q')
            break;
    }
    system("clear");
}
