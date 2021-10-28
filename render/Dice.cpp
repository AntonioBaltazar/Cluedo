#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>
#include "Dice.h"
#include "../Utils.h"
#include "Dice.h"

Dice::Dice() {}
Dice::Dice(int x, int y, int value) : m_x(x), m_y(y), m_value(value), m_wmax(0) {}
Dice::~Dice() {}

int Dice::getX() const { return m_x; }
int Dice::getY() const { return m_y; }
int Dice::getValue() const { return m_value; }
int Dice::getWmax() const { return m_wmax; }

void Dice::setX(int x) { m_x = x; }
void Dice::setY(int y) { m_y = y; }
void Dice::setValue(int value) { m_value = value; }
void Dice::setWmax(int wmax) { m_wmax = wmax; }

void Dice::random(int maxValue = 6) { setValue(rand() % maxValue + 1); }

void diceMenu()
{
    system("cls");
    std::cout << color("Dice menu :", Color::Bright_Blue) << std::endl;
    Dice d(40, 4, 6);
    int nb = 1;
    d.render();
    while(!kbhit())
    {
        //d.random();
        d.setValue(nb%6 + 1);
        nb++;
        d.render();
        Sleep(1000);
    }

}

void Dice::render()
{
    std::ifstream f;
    std::string content;
    std::vector<std::string> s;
    std::vector<std::vector<std::string>> datas;

    f.open("ressources/dice" + std::to_string(getValue()) + ".txt");

    //Reading data from the file, line by line
    while (std::getline(f, content))
    {
        if (content[0] == '#')
        {
            content.erase(0, 1);
            std::vector<std::string> configParam = strSplit(content, ":");
            if (configParam[0] == "wmax" && stoi(configParam[1]) > 0)
            {
                setWmax(stoi(configParam[1]));
                std::cout << "debug" << getWmax() << std::endl;
            }
        } else
            datas.push_back(strSplit(content, " "));
    }

    //Data display
    for (size_t i = 0; i < datas.size(); i++)
        for (size_t j = 0; j < datas[i].size(); j++)
        {
            int coeff = datas[i].size() > (size_t)getWmax() ? 1 : 2;
            gotoxy(getX()*2 + j*coeff, getY() + i);
            std::vector<std::string> caseDatas = strSplit(datas[i][j], ":");
            unsigned char ansi = caseDatas[0].size() >= 3 ? char(stoi(caseDatas[0])) : '\0';
            if (ansi != '\0')
            {
                std::cout << "\033[" + caseDatas[1] + "m";
                if (caseDatas[0] == "000")
                    std::cout << " ";
                else
                    std::cout << ansi;
                std::cout << "\033[0m";
            } else
                std::cout << color(caseDatas[0], getColor(std::stoi(caseDatas[1])));
        }
    std::cout << std::endl;
    f.close();
}
