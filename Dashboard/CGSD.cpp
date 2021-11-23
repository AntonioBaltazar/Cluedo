#include <iostream>
#include "Dashboard.h"
#include <conio.h>
#include "../Utils.h"

// Constructors & Destructor
Dashboard::Dashboard() {};
Dashboard::Dashboard(int trslX, int trslY, int maxX, int maxY)
{
    setTranslated(trslX, trslY);
    setMax(maxX, maxY);
};
Dashboard::~Dashboard() {}

// Methods
void Dashboard::renderTurn(Player* p)
{
    printAt(getMaxX(), getMaxY(), p->getName());
}

