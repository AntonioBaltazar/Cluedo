#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <algorithm>
#include "AnimatedElement.h"
#include "Utils.h"
#include "render/Square.h"

// Constructors & Destructor
AnimatedElement::AnimatedElement() {}
AnimatedElement::AnimatedElement(int translatedX, int translatedY) : m_translatedX(translatedX), m_translatedY(translatedY) {}
AnimatedElement::~AnimatedElement() {}

// Getters
int AnimatedElement::getTranslatedX() const { return m_translatedX; }
int AnimatedElement::getTranslatedY() const { return m_translatedY; }
int AnimatedElement::getMaxX() const { return m_maxX; }
int AnimatedElement::getMaxY() const { return m_maxY; }

// Setters
void AnimatedElement::setTranslatedX(int translatedX) { m_translatedX = translatedX; }
void AnimatedElement::setTranslatedY(int translatedY) { m_translatedY = translatedY; }
void AnimatedElement::setMaxX(int maxX) { m_maxX = maxX; }
void AnimatedElement::setMaxY(int maxY) { m_maxY = maxY; }

// Methods

void AnimatedElement::saveAsWorld(std::vector<Square>& world, std::string worldName)
{
    std::ifstream f;
    std::string content;

    Color current = Color::Bright_White;
    f.open("ressources/" + worldName + ".txt");

    //Reading data from the file, line by line
    while (std::getline(f, content))
    {
        if (content[0] == '-')
        {
            SquareType type = content[1] - '0' == 1 ? SquareType::TELEPORTER :
                content[1] - '0' == 2 ? SquareType::NPC : SquareType::WALL;
            world.back().setType(type);
            if (type == SquareType::TELEPORTER && strSplit(content, ":").size() > 1)
            {
                // If the square is an element
                world.back().setTpPath(strSplit(content, ":")[1]);
                world.back().getCoord().first = std::stoi(strSplit(content, ":")[2]);
                world.back().getCoord().second = std::stoi(strSplit(content, ":")[3]);
            }
        } else if (content[0] == '%')
        {
            content.erase(remove(content.begin(), content.end(), '%'), content.end());
            current = getColor(std::stoi(content));
        } else if (content[0] == '$')
        {
            content.erase(remove(content.begin(), content.end(), '$'), content.end());
            std::vector<std::string> strs = strSplit(content, ":");
            for (int i = std::stoi(strs[0]); i < std::stoi(strs[2]); i++)
                for (int j = std::stoi(strs[1]); j < std::stoi(strs[3]); j++)
                    world.push_back(Square(i, j, char(std::stoi(strs[4])), current));
        } else if (content[0] != '#') {
            std::vector<std::string> strs = strSplit(content, ":");
            world.push_back(Square(std::stoi(strs[0]), std::stoi(strs[1]), char(std::stoi(strs[2])), current));
        }
    }
    f.close();
}

void AnimatedElement::render(std::string pathName)
{
    std::vector<std::string> cluedo;
    int delay(0);
    int maxX(0), maxY(0);

    std::ifstream f;
    std::string content;
    f.open("ressources/" + pathName + ".txt");

    //Reading data from the file, line by line
    while (std::getline(f, content))
    {
        if (content[0] == '@')
        {
            content.erase(remove(content.begin(), content.end(), '@'), content.end());
            delay = std::stoi(content);
        } else if (content[0] == '%')
        {
            content.erase(remove(content.begin(), content.end(), '%'), content.end());

            HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(H,std::stoi(strSplit(content, ":")[1])*16+std::stoi(strSplit(content, ":")[0]));

        } else if (content[0] == '$')
        {
            content.erase(remove(content.begin(), content.end(), '$'), content.end());
            std::vector<std::string> strs = strSplit(content, ":");
            for (int i = std::stoi(strs[0]); i < std::stoi(strs[2]); i++)
                for (int j = std::stoi(strs[1]); j < std::stoi(strs[3]); j++)
                {
                    gotoxy(getTranslatedX() + i, getTranslatedY() + j);
                    std::cout << char(std::stoi(strs[4]));
                    maxX = (maxX < i) ? i : maxX;
                    maxY = (maxY < j) ? j : maxY;
                    Sleep(delay);
                }
        } else if (content[0] != '#') {
            std::vector<std::string> strs = strSplit(content, ":");
            gotoxy(getTranslatedX() + std::stoi(strs[0]), getTranslatedY() + std::stoi(strs[1]));
            std::cout << char(std::stoi(strs[2]));
            maxX = (maxX < std::stoi(strs[0])) ? std::stoi(strs[0]) : maxX;
            maxY = (maxY < std::stoi(strs[1])) ? std::stoi(strs[1]) : maxY;
            Sleep(delay);
        }
    }

    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,0*16+15);

    f.close();
    setMaxX(maxX);
    setMaxY(maxY);
}

void AnimatedElement::clearArea(int width, int height)
{
    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
        {
            gotoxy(getTranslatedX() + i, getTranslatedY() + j);
            std::cout << " ";
        }
}
