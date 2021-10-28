#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <windows.h>

#include "Dice.h"
#include "../Utils.h"
#include "Dice.h"

// Constructors & Destructor
Dice::Dice() : GraphicElement() {}
Dice::Dice(int x, int y, std::string path, int value) : GraphicElement(x, y, path), m_value(value) {}
Dice::~Dice() {}

int Dice::getValue() const { return m_value; }

void Dice::setValue(int value) { m_value = value; }

void Dice::random(int maxValue = 6) { setValue(rand() % maxValue + 1); }

void Dice::render()
{
    GraphicElement::render(std::to_string(getValue()));
}

void diceMenu()
{
    system("cls");
    std::cout << color("Dice menu :", Color::Bright_Blue) << std::endl << std::endl;
    Dice d(40, 4, "dice", 6);
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
