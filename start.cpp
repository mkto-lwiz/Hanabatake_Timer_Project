#include <iostream>
#include <string>
#include <vector>
#include <windows.h> 
#include <conio.h>

void display_art() {
    std::cout << "#       #       #\n";
    std::cout << "##     ###     ##\n";
    std::cout << "###   #####   ###\n";
    std::cout << "#### ####### ####\n";
    std::cout << "#################\n";
    std::cout << "#################\n";
    std::cout << " ###############\n";
    std::cout << "   ###########\n";
    std::cout << "     #######\n";
    std::cout << "       ***\n";
    std::cout << "       ***\n";
    std::cout << "       ***\n";
}

void show_help() {
    std::cout << "Hanabatake CLI\n";
    std::cout << "Usage:\n";
    std::cout << "  Hanabatake            Show default message + art\n";
    std::cout << "  Hanabatake --no-art   Show message only\n";
    std::cout << "  Hanabatake --help     Show this help\n";
}

void enableANSI() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void draw(const std::vector<std::string>& opt, int selected) {

    for (size_t i = 0; i < opt.size(); i++) {
        if ((int)i == selected) {
            std::cout << "\033[31m\033[1m> " << opt[i] << "\033[0m\n";
        } else {
            std::cout << "  " << opt[i] << "\n";
        }
    }
    // move cursor below art instead of clearing
} // <-- FIX: close function


int main(int argc, char* argv[]) {
    enableANSI(); // enable colors

    bool showArt = true;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--help") {
            show_help();
            return 0;
        } else if (arg == "--no-art") {
            showArt = false;
        }
    }

    std::cout << "====================================================\n";
    std::cout << "Welcome to Hanabatake 花畑, ready to seize your day?\n";
    std::cout << "====================================================\n";

    if (showArt) {
        display_art();
    }

    std::vector<std::string> opt = {"Start Session","Check flower","Quit"};
    int selected = 0;
    std::cout << "\033[s";  
    while (true) {
        std::cout <<"\033[u";
        std::cout <<"\033[J";

        draw(opt, selected);
        
        std::cout << "\033[?25l";
        int ch = _getch();

        if (ch == 224 || ch == 0) {
            ch = _getch();

            if (ch == 72) { // UP
                selected = (selected - 1 + opt.size()) % opt.size();
            } else if (ch == 80) { // DOWN
                selected = (selected + 1) % opt.size();
            }
        } else if (ch == 13) { // ENTER
            break;
        }
    }
   std::cout <<"\033[?25h]";
   std::cout <<"\033[u\033[J"; 

    std::cout << "Selected: " << opt[selected] << "\n";
    return 0;
}