#include "App.h"

App::App()
{
    life_ = new Life(20, 20, 9898, 9899);
}

void App::PrintMenu(std::wostream& stream)
{
    stream << L"\033[30;47m\033[1m <space> \033[0m - New generation "
           << L"\033[30;47m\033[1m L \033[0m - Load "
           << L"\033[30;47m\033[1m S \033[0m - Save "
           << L"\033[30;47m\033[1m Q \033[0m - Exit" << std::endl;
}

int App::MyGetch()
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

std::vector<std::wstring> App::getPresetsFromFilesystem()
{
    std::vector<std::wstring> presets;
    for (auto& p : std::filesystem::directory_iterator("./presets")) {
        std::wstring s
                = p.path().wstring().substr(10, p.path().wstring().size() - 14);
        presets.push_back(s);
    }
    return presets;
}

void App::PrintPresets(
        const std::vector<std::wstring>& presets, int current_index)
{
    for (int i = 0; i < presets.size(); i++) {
        if (i == current_index) {
            std::wcout << L"\033[30;47m" << presets[i] << L"\033[0m\n";
        } else {
            std::wcout << presets[i] << L"\n";
        }
    }
}

std::wstring App::getCurrentPresetPath(const std::vector<std::wstring>& presets)
{
    int current_index = 0;
    int key = 0;

    while (key != KEY_ENTER) {
        if (key != KEY_SERVICE_KEY1 && key != KEY_SERVICE_KEY2) {
            system("clear");
            PrintMenu();
            PrintPresets(presets, current_index);
        }
        key = MyGetch();
        switch (key) {
        case KEY_DOWN:
            if (current_index == presets.size() - 1)
                current_index = 0;
            else
                current_index++;
            break;
        case KEY_UP:
            if (current_index == 0)
                current_index = presets.size() - 1;
            else
                current_index--;
            break;
        case KEY_ENTER:
            return L"presets/" + presets[current_index] + L".txt";
            break;
        case 'q':
        case 'Q':
            return L"";
        default:
            break;
        }
    }
    return L"";
}

void App::Run()
{
    int c = 0;
    std::wstring preset = L"";
    while (c != 'q' && c != 'Q') {
        system("clear");
        PrintMenu();
        life_->Print();
        switch (c = MyGetch()) {
        case 'q':
        case 'Q':
            break;
        case 'l':
        case 'L':
            preset = getCurrentPresetPath(getPresetsFromFilesystem());
            if (preset != L"") {
                delete life_;
                life_ = new Life(preset);
            }
            break;
        case ' ':
            life_->MakeStep();
            break;
        default:
            // std::cout << c << ' ';
            break;
        }
    }
}

App::~App()
{
    delete life_;
}