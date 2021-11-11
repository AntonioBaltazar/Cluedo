#include <iostream>
#include <algorithm>
#include <conio.h>
#include <thread>
#include <string>
#include <mutex>
#include <windows.h>
#include "Blackhole.h"
#include "../GraphicElement.h"
#include "../Utils.h"

// Constructors & Destructor
Blackhole::Blackhole() { GraphicElement::loadDatasFromFile("");}
Blackhole::Blackhole(int x, int y, std::string path, std::string name) : GraphicElement(x, y, path), m_name(name)
{
    GraphicElement::loadDatasFromFile("");
    getTemp().push_back("186:37");
    getTemp().push_back("179:94");
}
Blackhole::~Blackhole() {}

// Getters
std::string Blackhole::getName() const { return m_name; }
std::vector<std::string>& Blackhole::getTemp() { return m_temp; }

// Setters
void Blackhole::setName(std::string name) { m_name = name; }
void Blackhole::setTemp(std::vector<std::string> temp) { m_temp = temp; }

// Methods
void Blackhole::render(std::string title = "", std::string playerName = "")
{
    std::mutex lock;

    auto f1 = [&lock, this](std::string title, std::string playerName){
        std::string suffix = "AIE! ";
        std::vector<std::pair<std::string, Color>> words;
        words.push_back(std::pair<std::string, Color>(suffix, Color::Red));
        words.push_back(std::pair<std::string, Color>(playerName, Color::Bright_Red));
        words.push_back(std::pair<std::string, Color>(title, Color::White));

        int currentX = 0;
        // TypeWriter's effect
        for (const auto& word : words)
        {
            std::string str = word.first;
            for (size_t i = 0; i < str.size(); i++) {
                lock.lock();
                gotoxy(getX()*2 + getDatas()[0].size() - (suffix.size() + title.size() + playerName.size())/2 + currentX, getDatas().size() + 3);
                std::cout << "" + color(str[i], word.second);
                currentX++;
                lock.unlock();
                Sleep(rand() % 50 + 25);
            }
        }
    };

    auto f2 = [&lock, this]() {
        while (!kbhit())
        {
            lock.lock();
            GraphicElement::render();
            translateDatas();
            lock.unlock();
            Sleep(100);

        }
    };

    std::thread typeWriting(f1, title, playerName);
    std::thread blackholeRunning(f2);

    typeWriting.join();
    blackholeRunning.join();
}

void Blackhole::translateDatas()
{
    for (int j = 0; j < 2; j++)
    {
        // Keep in memory the blocks hidden by the event horizon
        getTemp()[j] = getDatas()[12-1][13+j];

        // Down shifting
        std::string temp = getDatas()[getDatas().size()-1][13+j];
        for (int i = getDatas().size() - 1; i > 0; i--)
            getDatas()[i][13+j] = getDatas()[i-1][13+j];

        // Change the block of the previous hidden
        getDatas()[0][13+j] = temp;
        getDatas()[14][13+j] = "176:93";
        getDatas()[14+1][13+j] = temp;

        // Keep in memory the blocks hidden by the event horizon
        getTemp()[j] = getDatas()[14-1][13+j];
    }
}
