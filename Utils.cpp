#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <conio.h>
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

std::string color(unsigned char ch, Color c)
{
    std::string value = std::to_string(as_integer(c));
    return "\033[" + value + std::string("m") + std::to_string((unsigned char)ch) + "\033[0m";
}

std::string color(char ch, Color c)
{
    std::string value = std::to_string(as_integer(c));
    return "\033[" + value + std::string("m") + ch + "\033[0m";
}


Color getColor(int c)
{
    switch (c)
    {
        case 30: return Color::Black;
        case 31: return Color::Red;
        case 32: return Color::Green;
        case 33: return Color::Yellow;
        case 34: return Color::Blue;
        case 35: return Color::Magenta;
        case 36: return Color::Cyan;
        case 37: return Color::White;
        case 90: return Color::Bright_Black;
        case 91: return Color::Bright_Red;
        case 92: return Color::Bright_Green;
        case 93: return Color::Bright_Yellow;
        case 94: return Color::Bright_Blue;
        case 95: return Color::Bright_Magenta;
        case 96: return Color::Bright_Cyan;
        case 97: return Color::Bright_White;
        default: return Color::White;
    }
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

int getInput()
{
    while(!kbhit());
    int c = getch();
    return c;
}

void printAt(int x, int y, std::string str)
{
    gotoxy(x, y);
    std::cout << str;
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
