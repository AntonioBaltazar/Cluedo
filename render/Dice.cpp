#include <iostream>
#include <string>
#include <queue>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "../Utils.h"
#include "Blackhole.h"
#include "Dice.h"
#include "../Dialog.h"
#include "../scenes/Menu.h"
#include "../AnimatedElement.h"

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

void Dice::throwing()
{
    AnimatedElement border(0, 0);
    AnimatedElement value(2,1);
    border.render("dice/border");
    srand(time(NULL));
    int r;
    int v = 0;
    for (int i = 0; i < 40; i++)
    {
        r = rand() % 6 + 1;
        value.clearArea(9, 5);
        value.render("dice/" + std::to_string(r));
        int sleep = (float)1/(i/2+1) * 180;
        Sleep(sleep);
        v++;
    }
}

void Dice::render()
{
    throwing();
    //GraphicElement::loadDatasFromFile(std::to_string(getValue()));
    //GraphicElement::render();
}

void diceMenu()
{
    system("cls");
    Dice d;
    d.throwing();

    while(!kbhit());

}

