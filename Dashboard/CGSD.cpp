#include <iostream>
#include "Dashboard.h"
#include <conio.h>
#include "../Utils.h"
#include "../Dialog.h"

// Constructors & Destructor
Dashboard::Dashboard() {}
Dashboard::Dashboard(int trslX, int trslY, int maxX, int maxY)
{
    setTranslated(trslX, trslY);
    setMax(maxX, maxY);
    Dialog dTemp;
    dTemp.displayBordersPers(trslX, trslX + maxX, trslY, trslY + maxY);
}
Dashboard::~Dashboard() {}

// Methods
void Dashboard::renderTurn(Player* p)
{
    int paddingX = 2;
    int paddingY = 1;
    for (int i = 0; i < 10; i++)
        printAt(getTranslatedX() + 2, getTranslatedY() + 1 + i, std::string(20, ' '));
    std::string totalName = color(p->getName(), p->getColorName()) + color(" c'est a votre tour", Color::Bright_White;
    std::string splitTotalName = strSplit(totalName, " ");
    for (int i = 0; i < splitTotalName.size(); i++) {

    }
    printAt(getTranslatedX() + paddingX, getTranslatedY() + paddingY, color(p->getName(), p->getColorName()) + color(" c'est a votre tour", Color::Bright_White));

}

