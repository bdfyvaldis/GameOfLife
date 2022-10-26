#pragma once
#include "Life.h"
#include <algorithm>
#include <filesystem>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <vector>

class App {
public:
    App();
    void MainLoop();
    virtual ~App();
private:
    int MyGetch();
    static const int KEY_ENTER = 10;
    static const int KEY_SERVICE_KEY1 = 27;
    static const int KEY_SERVICE_KEY2 = 91;
    static const int KEY_DOWN = 66;
    static const int KEY_UP = 65;
    void PrintMenu(std::wostream& stream = std::wcout);
    std::wstring getCurrentPresetPath(const std::vector<std::wstring>& presets);
    std::vector<std::wstring> getPresetsFromFilesystem();
    Life* life_;
    void
    PrintPresets(const std::vector<std::wstring>& presets, int current_preset);
    void SaveCurrentState();
};