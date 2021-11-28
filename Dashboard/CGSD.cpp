#include <iostream>
#include "Dashboard.h"
#include <conio.h>
#include "../Utils.h"
#include "../Dialog.h"
#include "../World.h"

// Constructors & Destructor
Dashboard::Dashboard() {}
Dashboard::Dashboard(int trslX, int trslY, int maxX, int maxY)
{
    setTranslated(trslX, trslY);
    setMax(maxX, maxY);

}
Dashboard::~Dashboard() {}

// Methods
void Dashboard::renderTurn(Player* p, std::string location)
{
    Dialog dTemp;
    dTemp.displayBordersPers(getTranslatedX(), getTranslatedX() + getMaxX(), getTranslatedY(), getTranslatedY() + getMaxY());
    // Clearing old area
    int paddingX = 2 + getTranslatedX();
    int paddingY = 1 + getTranslatedY();
    for (int i = 0; i < getMaxY() - 1; i++)
        printAt(getTranslatedX() + 2, getTranslatedY() + 1 + i, std::string(getMaxX() - 2, ' '));

    // {Player} is your turn
    printAt(paddingX, paddingY, color(p->getName(), p->getColorName()));
    printBackToLine(strSplit("c'est \x85 votre tour !", " "), paddingX, paddingY, 22, p->getName().size() + 1, Color::Bright_White);

    // Commands list
    int padCmd(3);
    printAt(paddingX, paddingY + padCmd, color("\x18 \x19 \x1a <-", Color::Bright_Cyan) + color(" Se d\x82placer", Color::White));
    printAt(paddingX, paddingY + padCmd + 1, color("Espace", Color::Bright_Cyan) + color(" Int\x82ragir", Color::White));
    printAt(paddingX, paddingY + padCmd + 2, color("Touche H", Color::Bright_Cyan) + color(" Hypoth\x8Ase", Color::White));
    printAt(paddingX, paddingY + padCmd + 3, color("Touche N", Color::Bright_Cyan) + color(" Notes", Color::White));

    // Cards
    int padCard(8);
    printAt(paddingX, paddingY + padCard, color("Vos cartes :", Color::Bright_White));
    printAt(paddingX, paddingY + padCard + 1, color("-", Color::White) + color(" " + p->getPlayerPackage()[0].getName(), Color::Yellow));
    printAt(paddingX, paddingY + padCard + 2, color("-", Color::White) + color(" " + p->getPlayerPackage()[1].getName(), Color::Blue));
    printAt(paddingX, paddingY + padCard + 3, color("-", Color::White) + color(" " + p->getPlayerPackage()[2].getName(), Color::Magenta));

    // Location
    printAt(paddingX, paddingY + 13, color("Lieu : ", Color::Bright_White) +  color(location, Color::Bright_Yellow));

    // Number of possible movement
    int padMvt(getMaxY() - 3);
    if (p->getMovementAvailable() == -1)
        printBackToLine(strSplit("D\x82placements illimit\x82s", " "), paddingX, paddingY + padMvt + 1, 22, 0, Color::White);
    else if (p->getMovementAvailable() == 0)
        printBackToLine(strSplit("Aucun d\x82placement", " "), paddingX, paddingY + padMvt + 1, 22, 0, Color::White);
    else {
        std::string s = p->getMovementAvailable() == 1 ? "" : "s";
        printAt(paddingX, paddingY + padMvt + (s == "s" ? 0 : 1), color(std::to_string(p->getMovementAvailable()), Color::Bright_Red));
        printBackToLine(strSplit("d\x82placement" + s + " restant" + s, " "), paddingX, paddingY + padMvt + (s == "s" ? 0 : 1), 22, 2, Color::Bright_White);
    }
}

void Dashboard::printBackToLine(std::vector<std::string> strs, int x, int y, int maxLenght, int length, Color cl)
{
    int index(0);
    for (auto& str : strs) {
        if (length + str.size() > maxLenght) {
            length = 0;
            index++;
        }
        printAt(x + length, y + index, color(str, cl));
        length += str.size() + 1;
    }
}

