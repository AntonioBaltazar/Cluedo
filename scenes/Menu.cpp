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
#include "../Game.h"

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

void Menu::launch()
{
    render();
    Game g;
    int input, choice = 1;
    std::string sentences[] = {"1. Nouvelle partie", "2. Reprendre une partie", "3. R\x8agles du jeu", "4. Tableau des scores", "5. Cr\x82\dits", "6. Quitter"};

    while (1)
    {
        do
        {
            if (input == 75 && choice > 1) choice--;
            if (input == 77 && choice < 6) choice++;
            for (int i = 0; i < 40; i++) printAt(40+i, 20, " ");
            gotoxy(46, 20);
            std::cout << (choice > 1 ? char(17) : ' ');
            gotoxy(74, 20);
            std::cout << (choice < 6 ? char(16) : ' ');
            printAt(60 - sentences[choice-1].size()/2, 20, color(sentences[choice-1], Color::Bright_Cyan));
            input = getInput();
        } while (input != 13);

        switch(choice)
        {
            case 1 :
                g.start2();
                break;
            case 2 :
                g.lunchFromSave();
                g.run();
                break;
            case 3 :
                g.rules();
                break;
            case 4 :
                break;
            case 5 :
                g.credits();
                break;
            case 6 :
                PostMessage(GetConsoleWindow(), WM_CLOSE, 0, 0);
                break;
        }
        system("cls");
        render();
        input = 0;
    }
}
