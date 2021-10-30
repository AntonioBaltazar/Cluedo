#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>
#include "Menu.h"
#include "../Utils.h"

void Menu::render()
{
    system("cls");
    displayFile("menu");
    displayFile("menu2");
}

void Menu::displayFile(std::string fileName)
{
    std::vector<std::string> cluedo;
    bool timeable = true;

    std::ifstream f;
    std::string content;

    f.open("ressources/" + fileName + ".txt");

    //Reading data from the file, line by line
    while (std::getline(f, content))
    {
        if (content[0] == '@')
            timeable = content[1];
        else if (content[0] != '#')
            cluedo.push_back(content);

    }

    f.close();

    for (size_t i = 0; i < cluedo.size(); i++) {
        std::vector<std::string> strs = strSplit(cluedo[i], ":");
        gotoxy(std::stoi(strs[0]), std::stoi(strs[1]));
        std::cout << char(std::stoi(strs[2]));
        if (timeable)
            Sleep(rand() % 50);
    }

    while(!kbhit());

}
