#include <iostream>
#include <algorithm>
#include <conio.h>
#include <string>
#include <windows.h>
#include "Blackhole.h"
#include "../GraphicElement.h"
#include "../Utils.h"

// Constructors & Destructor
Blackhole::Blackhole() { GraphicElement::loadDatasFromFile("");}
Blackhole::Blackhole(int x, int y, std::string path, std::string name) : GraphicElement(x, y, path), m_name(name) { GraphicElement::loadDatasFromFile(""); }
Blackhole::~Blackhole() {}

// Getters
std::string Blackhole::getName() const { return m_name; }
std::vector<std::string> Blackhole::getTemp() const { return m_temp; }

// Setters
void Blackhole::setName(std::string name) { m_name = name; }
void Blackhole::setTemp(std::vector<std::string> temp) { m_temp = temp; }

// Methods
void Blackhole::render()
{
    for (int i = 0; i < 100; i++)
    {
        GraphicElement::render();
        translateDatas();
        Sleep(100);
    }
}

void Blackhole::translateDatas()
{
    for (int j = 0; j < 2; j++)
    {
        /*system("cls");
        for (size_t i = 0; i < getDatas().size()-1; i++)
            std::cout << getDatas()[i][13+j] << std::endl;
    */
        // Down shifting
        std::string temp = getDatas()[getDatas().size()-1][13+j];
        for (int i = getDatas().size() - 1; i > 1; i--)
            getDatas()[i][13+j] = getDatas()[i-1][13+j];
        getDatas()[0][13+j] = temp;
/*
        for (size_t i = 0; i < getDatas().size()-1; i++) {
            gotoxy(20, i);
            std::cout << getDatas()[i][13+j];
       }
        while(!kbhit());
        char c = getch();*/
    }
}

