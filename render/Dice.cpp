#include <iostream>
#include <string>
#include <queue>
#include <conio.h>
#include <windows.h>
#include "../Utils.h"
#include "Blackhole.h"
#include "Dice.h"
#include "../Dialog.h"
#include "../scenes/Menu.h"

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

    /*Dialog d;
    Person martin("MARTIN", Color::Bright_Cyan);
    Person tonio("ANTONIO", Color::Bright_Green);
    Person emma("EMMA", Color::Bright_Magenta);
    std::queue<Message> msgs;
    msgs.push(Message(tonio, "Lorem ipsum dolor sit amet, consectetur adipiscing elit. Donec ex tortor, commodo nec ligula sit amet, condimentum bibendum erat. Suspendisse potenti."));
    msgs.push(Message(martin, "*marche dans les couloirs avec Tonio*"));
    msgs.push(Message(emma, "bouh"));
    msgs.push(Message(tonio, "Ouhhouhh c'est la maison de l'horreur ici.."));

    d.getMessages() = msgs;

    d.displayConversation();*/
    Menu m;
    m.render();
    system("cls");
    Blackhole bh(15, 2, "blackhole", "Trou noir");
    bh.render(" passe un tour dans le trou noir seul..", "Martin");
}

