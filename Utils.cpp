#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <string>
#include <vector>
#include "Utils.h"

template <typename Enumeration>
auto as_integer(Enumeration const value)
    -> typename std::underlying_type<Enumeration>::type
{
    return static_cast<typename std::underlying_type<Enumeration>::type>(value);
}

std::string color(std::string str, Color c)
{
    std::string value = std::to_string(as_integer(c));
    return "\033[" + value + std::string("m") + str + "\033[0m";
}

/// https://stackoverflow.com/questions/4053837/colorizing-text-in-the-console-with-c
void activateVirtualTerminal()
{
    HANDLE handleOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD consoleMode;
    GetConsoleMode( handleOut , &consoleMode);
    consoleMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    consoleMode |= DISABLE_NEWLINE_AUTO_RETURN;
    SetConsoleMode( handleOut , consoleMode );
}

std::vector<std::string> strSplit(std::string str, std::string delimiter)
{
    std::vector<std::string> res;
    size_t position = 0;

    while ((position = str.find(delimiter)) != std::string::npos)
    {
        res.push_back(str.substr(0, position));
        str.erase(0, position + delimiter.length());
    }
    res.push_back(str);
    return res;
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
