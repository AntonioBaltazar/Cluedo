#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include <mutex>
#include <thread>
#include "Menu.h"
#include "../Utils.h"

void Menu::render()
{
    system("cls");
    std::mutex lock;
    auto f = [&lock, this](std::string fileName, int translateX, int translateY) {
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
                        lock.lock();
                        gotoxy(translateX + i, translateY + j);
                        std::cout << char(std::stoi(strs[4]));
                        lock.unlock();
                        Sleep(delay);
                    }
            } else if (content[0] != '#') {
                std::vector<std::string> strs = strSplit(content, ":");
                lock.lock();
                gotoxy(translateX + std::stoi(strs[0]), translateY + std::stoi(strs[1]));
                std::cout << char(std::stoi(strs[2]));
                lock.unlock();
                Sleep(delay);
            }
        }

        HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(H,getBackgroundColor()*16+getTextColor());

        f.close();
    };

    std::thread l1(f, "menu/letters/c", 41, 9);
    std::thread l2(f, "menu/letters/l", 41, 9);
    std::thread l3(f, "menu/letters/u", 41, 9);
    std::thread l4(f, "menu/letters/e", 41, 9);
    std::thread l5(f, "menu/letters/d", 41, 9);
    std::thread l6(f, "menu/letters/o", 41, 9);
    l1.join();
    l2.join();
    l3.join();
    l4.join();
    l5.join();
    l6.join();
    renderHorizontalBar(47, 9);
    //displayFile("menu", 41, 9);
    //displayFile("menu2", 41, 9);
    //displayFile("menu3", 41, 9);
    //displayFile("menu4", 41, 9);

    while(!kbhit());
    int ch = getch();
}

void Menu::renderHorizontalBar(int translateX, int translateY)
{
    for (int i = 0; i < 20; i++)
    {
        gotoxy(translateX + 12 - i, translateY + 8);
        std::cout << char(std::stoi("205"));
        gotoxy(translateX + 13 + i, translateY + 8);
        std::cout << char(std::stoi("205"));
        Sleep(40);
    }
}
