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
    int input(0);
    do {
        int indexX(str.size() % (getMaxX() - 2)), indexY(str.size() / (getMaxX() - 2));
        input = getInput();

        if (((input >= 'a' && input <= 'z') || (input >= 'A' && input <= 'Z') || input == ' '))
        {
            str += (char)input;
            printAt(getTranslatedX() + indexX + 1, getTranslatedY() + indexY, std::string(1, char(input)));
        }
        else if (input == 8 && indexX > 0)
        {
            str.pop_back();
            printAt(getTranslatedX() + indexX - 1, getTranslatedY() + indexY, " ");
        }

    } while (input != 27);
    return str;
}
