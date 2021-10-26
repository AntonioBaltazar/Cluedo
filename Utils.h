#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#define DISABLE_NEWLINE_AUTO_RETURN  0x0008

enum class Color
{
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
    Bright_Black = 90,
    Bright_Red = 91,
    Bright_Green = 92,
    Bright_Yellow = 93,
    Bright_Blue = 94,
    Bright_Magenta = 95,
    Bright_Cyan = 96,
    Bright_White = 97
};

void gotoxy(int x, int y);
void ShowConsoleCursor(bool showFlag);
std::string color(std::string str, Color c);
void activateVirtualTerminal();

#endif // UTILS_H_INCLUDED
