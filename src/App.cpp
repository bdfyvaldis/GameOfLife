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

void App::MainLoop()
{
    int c = 0;
    std::wstring preset_to_load = L"";
    bool flag_success_save = false;
    while (c != 'q' && c != 'Q') {
	std::wcout << L"\033[1;1H";
        PrintMenu();
        life_->Print();
        if (flag_success_save) {
            std::wcout << "\033[32mState successfuly saved!";
            flag_success_save = false;
        }
        switch (c = MyGetch()) {
        case 'q':
        case 'Q':
            break;
        case 'l':
        case 'L':
            preset_to_load = getCurrentPresetPath(getPresetsFromFilesystem());
            if (preset_to_load != L"") {
                delete life_;
                life_ = new Life(preset_to_load);
            }
            break;
        case 'S':
        case 's':
            SaveCurrentState();
            flag_success_save = true;
            break;
        case ' ':
            life_->MakeStep();
            break;
        default:
            break;
        }
    }
}

void App::SaveCurrentState()
{
    system("clear");
    std::wstring new_preset_name;
    while (true) {
        std::wcout << L"Type name of new preset.. ";
        std::string preset_name_str;
        std::cin >> preset_name_str;
        new_preset_name
                = std::wstring(preset_name_str.begin(), preset_name_str.end());
        auto presets_list = getPresetsFromFilesystem();
        if (std::find(presets_list.begin(), presets_list.end(), new_preset_name)
            != presets_list.end()) {
            std::wcout << L"File " << new_preset_name << L".txt already exists."
                       << std::endl;
            continue;
        }
        break;
    }
    life_->Save(L"presets//" + new_preset_name + L".txt");
}

App::~App()
{
    delete life_;
}
