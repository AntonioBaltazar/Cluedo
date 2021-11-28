#include <iostream>
#include "../AnimatedElement.h"
#include "../Utils.h"
#include "Notepad.h"
#include "../Dialog.h"

// Constructors & Destructor
Notepad::Notepad() {}
Notepad::Notepad(int trslX, int trslY, int maxX, int maxY)
{
   init(trslX, trslY, maxX, maxY);
}

void Notepad::init(int trslX, int trslY, int maxX, int maxY)
{
    setTranslated(trslX, trslY);
    setMax(maxX, maxY);
    for (int i = 0; i < getMaxY(); i++)
        printAt(getTranslatedX(), getTranslatedY() + i, std::string(getMaxX(), ' '));
    Dialog dTemp;
    dTemp.displayBordersPers(trslX, trslX + maxX, trslY, trslY + maxY);
}

Notepad::~Notepad() {}
// Getters
std::string Notepad::getContent() { return m_content; }
// Setters
void Notepad::setContent(std::string content) { m_content = content; }
// Methods!
void Notepad::renderTurn()
{
    init(getTranslatedX(), getTranslatedY(), getMaxX(), getMaxY());
    printAt(getTranslatedX() + 2, getTranslatedY() + 1, color("Bloc-notes", Color::White));
}

std::string Notepad::open(std::string str)
{
    int i = 0;
    for (auto& s : str) {
        printAt(getTranslatedX() + 2 + i%(getMaxX() - 3), getTranslatedY() + 2 + i/(getMaxX() - 3), s);
        i++;
    }

    int input(0);
    do {
        int indexX((str.size() - 1) % (getMaxX() - 3)), indexY((str.size() - 1) / (getMaxX() - 3)%getMaxY());
        input = getInput();

        if (((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z') || input == ' ') && !(indexX + 1 == getMaxX() - 3 && indexY == getMaxY() - 3))
        {
            str += (char)input;
            indexX = (str.size() - 1) % (getMaxX() - 3);
            indexY = (str.size() - 1) / (getMaxX() - 3);
            printAt(getTranslatedX() + indexX + 2, getTranslatedY() + indexY + 2, std::string(1, char(input)));
        } else if (input == 8 && str.size() > 0)
        {
            str.pop_back();
            printAt(getTranslatedX() + indexX + 2, getTranslatedY() + indexY + 2, " ");
        }

    } while (input != 27);
    return str;
}
