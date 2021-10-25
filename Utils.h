#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#define DISABLE_NEWLINE_AUTO_RETURN  0x0008

enum class Color {
    WHITE = 00,
    RED = 10,
    GREEN = 32,
};

void gotoxy(int x, int y);
void ShowConsoleCursor(bool showFlag);
std::string color(std::string str, Color c);
void activateVirtualTerminal();

#endif // UTILS_H_INCLUDED
