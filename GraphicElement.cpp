#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "GraphicElement.h"
#include "Utils.h"

//Constructors & Destructor
GraphicElement::GraphicElement() {}
GraphicElement::GraphicElement(int x, int y, std::string path) : m_x(x), m_y(y), m_maxWidth(0), m_path(path) {}
GraphicElement::~GraphicElement() {}

//Getters
int GraphicElement::getX() const { return m_x; }
int GraphicElement::getY() const { return m_y; }
int GraphicElement::getMaxWidth() const { return m_maxWidth; }
std::string GraphicElement::getPath() const { return m_path; }

//Setters
void GraphicElement::setX(int x) { m_x = x; }
void GraphicElement::setY(int y) { m_y = y; }
void GraphicElement::setMaxWidth(int maxWidth) { m_maxWidth = maxWidth; }
void GraphicElement::setPath(std::string path) { m_path = path; }

//Methods
void GraphicElement::render(std::string extravalue = "")
{
    std::ifstream f;
    std::string content;
    std::vector<std::string> s;
    std::vector<std::vector<std::string>> datas;

    f.open("ressources/" + getPath() + extravalue + ".txt");

    //Reading data from the file, line by line
    while (std::getline(f, content))
    {
        if (content[0] == '#')
        {
            content.erase(0, 1);
            std::vector<std::string> configParam = strSplit(content, ":");
            if (configParam[0] == "wmax" && stoi(configParam[1]) > 0)
                setMaxWidth(stoi(configParam[1]));
        } else
            datas.push_back(strSplit(content, " "));
    }

    //Data display
    for (size_t i = 0; i < datas.size(); i++)
        for (size_t j = 0; j < datas[i].size(); j++)
        {
            int coeff = datas[i].size() > (size_t)getMaxWidth() ? 1 : 2;
            gotoxy(getX()*2 + j*coeff, getY() + i);
            std::vector<std::string> caseDatas = strSplit(datas[i][j], ":");
            //unsigned char ansi = caseDatas[0].size() >= 3 ? char(stoi(caseDatas[0])) : '\0';
            if (caseDatas[0].size() >= 3)
            {
                std::cout << "\033[" + caseDatas[1] + "m";
                if (caseDatas[0] == "xxx")
                    std::cout << " ";
                else
                    std::cout << char(stoi(caseDatas[0]));
                std::cout << "\033[0m";
            } else
                std::cout << color(caseDatas[0], getColor(std::stoi(caseDatas[1])));
        }
    std::cout << std::endl;
    f.close();
}
