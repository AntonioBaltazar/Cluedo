#include <iostream>
#include <string>
#include <windows.h>
#include <conio.h>

#include "Dialog.h"
#include "Utils.h"

// Constructos & Destructor
Dialog::Dialog() {
    setMaxX(117);
    setMaxY(7);
    setTranslatedX(2);
    setTranslatedY(22);
}
Dialog::Dialog(int trslX, int trslY, int maxX, int maxY)
{
    setTranslated(trslX, trslY);
    setMax(maxX, maxY);
}
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
    for (int i = 0; i < getMaxY(); i++)
        printAt(getTranslatedX(), getTranslatedY() + i, std::string(getMaxX(), ' '));
    displayBordersPers(getTranslatedX(), getTranslatedX() + getMaxX(), getTranslatedY(), getTranslatedY() + getMaxY());
    while (!getMessages().empty())
    {
        displayMessage();
        // Arrow
        while (!kbhit())
        {
            gotoxy(getTranslatedX() + getMaxX() - 4, getTranslatedY() + 2);
            std::cout << "\033[97m";
            std::cout << char(std::stoi("31"));
            std::cout << "\033[37m";
            if (kbhit()) break;
            Sleep(600);

            gotoxy(getTranslatedX() + getMaxX() - 4, getTranslatedY() + 2);
            std::cout << " ";
            if (kbhit()) break;
            Sleep(600);

        }
        char ch = getch();
        getMessages().pop();
    }
}

void Dialog::displayMessage()
{
    // Clearing old area
    for (int i = 0; i < getMaxY() - 2; i++)
        printAt(getTranslatedX() + 1, getTranslatedY() + i + 1, std::string(getMaxX() - 2, ' '));

    int startName = 10 - getMessages().front().getPerson().getName().size();
    int startMsg = 10 + 3;
    printAt(getTranslatedX() + 2 + startName, getTranslatedY() + 2, color(getMessages().front().getPerson().getName() + " : ", getMessages().front().getPerson().getColorName()));

    // TypeWriter's effect
    int letters = 0;
    for (const auto& word : strSplit(getMessages().front().getContent(), " "))
    {
        for (size_t i = 0; i < word.size(); i++) {
            if (letters == 76)
                gotoxy(getTranslatedX() + startMsg, getTranslatedY() + 2);
            if (letters == 152)
                gotoxy(getTranslatedX() + startMsg, getTranslatedY() + 3);
            std::cout << color(word[i], Color::White);
            Sleep(rand() % 45 + 20);
            letters++;
        }
        std::cout << " ";
    }

}


void Dialog::displayBorders(int topY = 22, int bottomY = 28)
{
    for (int i = 0; i < 8; i++)
        printAt(3, 23+i, std::string(120, ' '));

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

///Display borders with customized coordinates
void Dialog::displayBordersPers(int X, int X2,int Y, int Y2)
{
    // Top & Bottom
    for (int i = X; i < X2; i++)
    {
        gotoxy(1 + i, Y);
        std::cout << char(std::stoi("205"));
        gotoxy(1 + i, Y2);
        std::cout << char(std::stoi("205"));
    }

    // Corners
    gotoxy(X, Y);
    std::cout << char(std::stoi("201"));
    gotoxy(X2, Y);
    std::cout << char(std::stoi("187"));
    gotoxy(X, Y2);
    std::cout << char(std::stoi("200"));
    gotoxy(X2, Y2);
    std::cout << char(std::stoi("188"));

    // Left & Right
    for (int i = Y + 1; i < Y2; i++)
    {
        gotoxy(X2, i);
        std::cout << char(std::stoi("186"));
        gotoxy(X, i);
        std::cout << char(std::stoi("186"));
    }
}

///Display only the result of the hypothesis
void Dialog::displayMessResultHyp(int X,int Y, bool longText)
{
    // TypeWriter's effect
    int letters = 0;
    int limX1 = longText== true ? 50:36;
    int limX2 = longText== true ? 100:72;
    Color myColor;

    //Color's choice
    if(getMessages().front().getContent() == "En \x88tes vous sur ?"
       || getMessages().front().getContent() == "Vous pourriez peut-\x88tre vous rendre \x85 la case principale ?")
       myColor = Color::Cyan;
    else
       myColor = getMessages().front().getContent() == "H\x82las ce n'est pas la bonne r\x82ponse, vous avez perdu !"
                     ? Color::Red : Color::Green;

    gotoxy(X+10, Y+3);
    //Message Display
    for (const auto& word : strSplit(getMessages().front().getContent(), " "))
    {
        for (size_t i = 0; i < word.size(); i++)
        {
            if (letters == limX1)
                gotoxy(X+2, 12);
            if (letters == limX2)
                gotoxy(X+2, 13);
            std::cout << color(word[i], myColor);
            Sleep(rand() % 45 + 20);
            letters++;
        }
        std::cout << " ";
    }
    std::cout << "\n\n\n\n\n\n\n";
}


