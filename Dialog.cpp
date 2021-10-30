#include <iostream>
#include <string>
#include "Dialog.h"
#include "Utils.h"

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
void Dialog::displayMessage()
{
    for (int i = 0; i < 80; i++) {
        gotoxy(20+i, 18);
        std::cout << char(std::stoi("205"));
    }
    std::cout << std::endl;
}
