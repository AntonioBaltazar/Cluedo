#include <iostream>
#include <fstream>
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
    Dice d;
    d.render();
}

void Dice::render()
{
    std::ifstream f;
    std::string content;
    std::vector<std::vector<std::string>> datas;
    std::vector<std::string> s;

    f.open("ressources/dice6.txt");

    while (std::getline(f, content))
    {
        s = strSplit(content, " ");
        for (size_t i = 0; i < s.size(); i++)
            std::cout << color(s[i], Color::Cyan) << std::endl;
        std::cout << std::endl;
        datas.push_back(s);
    }

    for (size_t i = 0; i < datas.size(); i++)
        for (size_t j = 0; j < datas[i].size(); j++)
            std::cout << "ok" << std::endl;

    f.close();
}
