#include <iostream>
#include <string>
#include <queue>
#include <conio.h>
#include <windows.h>
#include <time.h>

#include "Dice.h"
#include "../scenes/Menu.h"
#include "../Utils.h"
#include "../Dialog.h"
#include "../AnimatedElement.h"
#include "Blackhole.h"

// Constructors & Destructor
Dice::Dice() {}
Dice::Dice(int trslX, int trslY, int maxX, int maxY) {
    setTranslatedX(trslX);
    setTranslatedY(trslY);
    setMaxX(maxX);
    setMaxY(maxY);
}

Dice::~Dice() {}

int Dice::throwing()
{
    AnimatedElement border(getTranslatedX(), getTranslatedY());
    AnimatedElement value(getTranslatedX() + 2, getTranslatedY() + 1);

    border.render("dice/border");
    srand(time(NULL));
    int rdm;
    for (int i = 0; i < 14; i++)
    {
        rdm = rand() % 6 + 1;
        value.clearArea(9, 5);
        value.render("dice/" + std::to_string(rdm));
        Sleep(rand()%180 + 80);
    }

    return rdm;
}

void diceMenu()
{
    system("cls");

    Blackhole bh(15, 2, "blackhole", "Trou noir");
    bh.render(" vient de tomber malheureusement dans un trou noir..", "Martin");
    /*
        Blackhole bh(14, 4, "blackhole", "bh");
        bh.render(" vient de tomber dans un trou noir :/", "Martin");
    */
    while(!kbhit());

}
