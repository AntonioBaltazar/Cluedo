#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include "../Utils.h"
#include "Blackhole.h"
#include "Dice.h"

// Constructors & Destructor
Dice::Dice() : GraphicElement() {}
Dice::Dice(int x, int y, std::string path, int value) : GraphicElement(x, y, path), m_value(value) {}
Dice::~Dice() {}

// Getters
int Dice::getValue() const { return m_value; }

// Setters
void Dice::setValue(int value) { m_value = value; }

// Methods
void Dice::random(int maxValue = 6) { setValue(rand() % maxValue + 1); }
void Dice::render()
{
    GraphicElement::loadDatasFromFile(std::to_string(getValue()));
    GraphicElement::render();
}

void diceMenu()
{
    system("cls");
    std::cout << color("Dice menu :", Color::Bright_Blue) << std::endl << std::endl;
    Blackhole bh(10, 2, "blackhole", "Trou noir");
    bh.render();
    //GraphicElement d(10, 3, "blackhole");
    //d.render("");
    /*Dice d(40, 4, "dice", 6);
    int nb = 1;
    d.render();
    while(!kbhit())
    {
        d.setValue(nb%6 + 1);
        nb++;
        d.render();
        Sleep(1000);
    }*/

}
