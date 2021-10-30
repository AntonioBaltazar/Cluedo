#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include "Menu.h"
#include "../Utils.h"

void Menu::render()
{
    system("cls");
    displayFile("menu", 41, 9);
    displayFile("menu2", 41, 9);
    displayFile("menu3", 41, 9);
    displayFile("menu4", 41, 9);

    while(!kbhit());
    int ch = getch();
}

void Menu::displayFile(std::string fileName, int translateX, int translateY)
{
    std::vector<std::string> cluedo;
    int delay = 0;

    std::ifstream f;
    std::string content;

    f.open("ressources/" + fileName + ".txt");

    //Reading data from the file, line by line
    while (std::getline(f, content))
    {
        if (content[0] == '@')
        {
            content.erase(remove(content.begin(), content.end(), '@'), content.end());
            delay = std::stoi(content);
        } else if (content[0] == '%')
        {
            content.erase(remove(content.begin(), content.end(), '%'), content.end());

            HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(H,std::stoi(strSplit(content, ":")[1])*16+std::stoi(strSplit(content, ":")[0]));

        } else if (content[0] == '$')
        {
            content.erase(remove(content.begin(), content.end(), '$'), content.end());
            std::vector<std::string> strs = strSplit(content, ":");
            for (int i = std::stoi(strs[0]); i < std::stoi(strs[2]); i++)
                for (int j = std::stoi(strs[1]); j < std::stoi(strs[3]); j++)
                {
                    gotoxy(translateX + i, translateY + j);
                    std::cout << char(std::stoi(strs[4]));
                    Sleep(delay);
                }
        } else if (content[0] != '#') {
            std::vector<std::string> strs = strSplit(content, ":");
            gotoxy(translateX + std::stoi(strs[0]), translateY + std::stoi(strs[1]));
            std::cout << char(std::stoi(strs[2]));
            Sleep(delay);
        }
    }

    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,getBackgroundColor()*16+getTextColor());

    f.close();
}
