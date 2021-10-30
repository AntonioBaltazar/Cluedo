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
    displayFile("menu");
    displayFile("menu2");
    displayFile("menu3");
}

void Menu::displayFile(std::string fileName)
{
    std::vector<std::string> cluedo;
    int timeable = 1;

    std::ifstream f;
    std::string content;

    f.open("ressources/" + fileName + ".txt");

    //Reading data from the file, line by line
    while (std::getline(f, content))
    {
        if (content[0] == '@')
            timeable = (int)content[1];
        else if (content[0] == '%')
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
                    gotoxy(i, j);
                    std::cout << char(std::stoi(strs[4]));
                    if (timeable == 1)
                        Sleep(rand() % 50);
                }
        } else if (content[0] != '#') {
            std::vector<std::string> strs = strSplit(content, ":");
            gotoxy(std::stoi(strs[0]), std::stoi(strs[1]));
            std::cout << char(std::stoi(strs[2]));
            if (timeable)
                Sleep(rand() % 50);
        }
    }

    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,getBackgroundColor()*16+getTextColor());

    f.close();

    /*for (size_t i = 0; i < cluedo.size(); i++) {
        std::vector<std::string> strs = strSplit(cluedo[i], ":");
        gotoxy(std::stoi(strs[0]), std::stoi(strs[1]));
        std::cout << char(std::stoi(strs[2]));
        if (timeable)
            Sleep(rand() % 50);
    }*/

    while(!kbhit());
    int ch = getch();

}
