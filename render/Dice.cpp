#include <iostream>
#include <string>
#include <queue>
#include <conio.h>
#include <windows.h>
#include <time.h>

#include "Dice.h"
#include "../Utils.h"
#include "../Dialog.h"
#include "../AnimatedElement.h"

// Constructors & Destructor
Dice::Dice() {}
Dice::Dice(int value) : m_value(value) {}
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

    int v = 0;
    for (int i = 0; i < 40; i++)
    {
        random(6);
        value.clearArea(9, 5);
        value.render("dice/" + std::to_string(getValue()));
        int sleep = (float)1/(i/2+1) * 180;
        Sleep(sleep);
        v++;
    }
}

void diceMenu()
{
    system("cls");
    Dice d;

    d.throwing();

    while(!kbhit());

}
