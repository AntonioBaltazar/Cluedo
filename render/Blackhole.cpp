#include <iostream>
#include <string>
#include <windows.h>
#include "Blackhole.h"
#include "../Utils.h"

// Constructors & Destructor
Blackhole::Blackhole() { setDatas(GraphicElement::render("")); }
Blackhole::Blackhole(int x, int y, std::string path, std::string name) : GraphicElement(x, y, path), m_name(name) { setDatas(GraphicElement::render("")); }
Blackhole::~Blackhole() {}

// Getters
std::string Blackhole::getName() const { return m_name; }
std::vector<std::vector<std::string>> Blackhole::getDatas() const { return m_datas; }
std::vector<std::string> Blackhole::getTemp() const { return m_temp; }

// Setters
void Blackhole::setName(std::string name) { m_name = name; }
void Blackhole::setDatas(std::vector<std::vector<std::string>> datas) { m_datas = datas; }
void Blackhole::setTemp(std::vector<std::string> temp) { m_temp = temp; }

// Methods
void Blackhole::render()
{
    for (int i = 0; i < 10; i++)
    {
        displayDatas();
        Sleep(400);
        translateDatas();
    }
}

void Blackhole::displayDatas()
{
    for (size_t i = 0; i < getDatas().size(); i++)
        for (size_t j = 0; j < getDatas()[i].size(); j++)
        {
            int coeff = getDatas()[i].size() > (size_t)getMaxWidth() ? 1 : 2;
            gotoxy(getX()*2 + j*coeff, getY() + i);
            std::vector<std::string> caseDatas = strSplit(getDatas()[i][j], ":");
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
}

void Blackhole::translateDatas()
{
    int loop = getDatas().size();
    std::vector<std::string> temp;
    temp.push_back(getDatas()[13][12]);
    temp.push_back(getDatas()[13][13]);
    temp.push_back(getDatas()[13][14]);
    temp.push_back(getDatas()[13][15]);
    setTemp(temp);

    for (int j = 0; j < 4; j++)
    {
        std::string tempStr = getDatas()[0][12+j];
        for (int i = 0; i < loop; i++)
        {
            if (i+1 < loop)
                getDatas()[i][12+j] = getDatas()[i+1][12+j];
        }

        getDatas()[loop-1][12+j] = tempStr;
    }
}

