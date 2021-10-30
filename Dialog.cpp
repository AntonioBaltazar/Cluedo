#include <iostream>
#include <string>
#include <windows.h>
#include "Dialog.h"
#include "Utils.h"
#include <conio.h>

// Constructos & Destructor
Dialog::Dialog() {}
Dialog::Dialog(std::queue<Message> msgs) : m_messages(msgs) {}
Dialog::~Dialog() {}

// Getters
std::queue<Message>& Dialog::getMessages() { return m_messages; }

// Setters
void Dialog::setMessages(std::queue<Message> msgs) { m_messages = msgs; }

// Methods
void Dialog::addMessage(Message msg) { getMessages().push(msg); }

void Dialog::displayConversation()
{
    displayBorders(22, 28);
    while (!getMessages().empty())
    {
        displayMessage();
        while (!kbhit());
        char ch = getch();
        getMessages().pop();
    }
}

void Dialog::displayMessage()
{
    gotoxy(12, 24);
    for (int i = 0; i < 106; i++)
    {
        std::cout << " ";
    }
    gotoxy(12, 24);
    std::cout << color(getMessages().front().getPerson().getName() + " : ", Color::Bright_Yellow);

    // TypeWriter's effect
    for (const auto& word : strSplit(getMessages().front().getContent(), " "))
    {
        for (size_t i = 0; i < word.size(); i++) {
            std::cout << color(word[i], Color::White);
            Sleep(rand() % 50 + 25);
        }
        std::cout << " ";
    }

}


void Dialog::displayBorders(int topY = 22, int bottomY = 28)
{
    // Top & Bottom
    for (int i = 0; i < 116; i++)
    {
        gotoxy(3 + i, 22);
        std::cout << char(std::stoi("205"));
        gotoxy(3 + i, 28);
        std::cout << char(std::stoi("205"));
    }

    // Corners
    gotoxy(2, 22);
    std::cout << char(std::stoi("201"));
    gotoxy(119, 22);
    std::cout << char(std::stoi("187"));
    gotoxy(2, 28);
    std::cout << char(std::stoi("200"));
    gotoxy(119, 28);
    std::cout << char(std::stoi("188"));

    // Left & Right
    for (int i = topY + 1; i < bottomY; i++)
    {
        gotoxy(119, i);
        std::cout << char(std::stoi("186"));
        gotoxy(2, i);
        std::cout << char(std::stoi("186"));
    }
}
