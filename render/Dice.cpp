#include <iostream>
#include <string>
#include <conio.h>
#include <windows.h>
#include "../Utils.h"
#include "Blackhole.h"
#include "Dice.h"
#include "../Dialog.h"

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
    //Blackhole bh(15, 2, "blackhole", "Trou noir");
    //bh.render(" passe un tour dans le trou noir seul..", "Martin");
    Dialog d;
    d.displayMessage();
}
