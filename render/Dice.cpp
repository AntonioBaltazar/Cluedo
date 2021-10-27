#include <iostream>
#include <fstream>
#include <string>
#include "Dice.h"
#include "../Utils.h"
#include "Dice.h"

Dice::Dice() {}
Dice::Dice(int x, int y, int value) : m_x(x), m_y(y), m_value(value) {}
Dice::~Dice() {}

int Dice::getX() const { return m_x; }
int Dice::getY() const { return m_y; }
int Dice::getValue() const { return m_value; }

void Dice::setX(int x) { m_x = x; }
void Dice::setY(int y) { m_y = y; }
void Dice::setValue(int value) { m_value = value; }

void Dice::random(int maxValue = 6) { setValue(rand() % maxValue + 1); }

void diceMenu()
{
    system("cls");
    std::cout << color("Dice menu :", Color::Bright_Blue) << std::endl;
    Dice d(40, 4, 6);
    d.render();
}

void Dice::render()
{
    std::ifstream f;
    std::string content;
    std::vector<std::vector<std::string>> datas;
    std::vector<std::string> s;

    f.open("ressources/dice" + std::to_string(getValue()) + ".txt");

    //Reading data from the file, line by line
    while (std::getline(f, content))
        datas.push_back(strSplit(content, " "));

    //Data display
    for (size_t i = 0; i < datas.size(); i++)
        for (size_t j = 0; j < datas[i].size(); j++)
        {
            gotoxy((getX() + i)*2, getY() + j);
            std::vector<std::string> caseDatas = strSplit(datas[j][i], ":");
            std::cout << color(caseDatas[0], getColor(std::stoi(caseDatas[1]))) << std::endl;
        }

    f.close();
}
