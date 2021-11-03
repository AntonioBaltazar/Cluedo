#ifndef DIALOG_H_INCLUDED
#define DIALOG_H_INCLUDED

#include <queue>
#include "Utils.h"
#include "Script/Script.h"

class Person {
private:
    std::string m_name;
    Color m_colorName;
public:
    Person() {}
    Person(std::string name, Color colorName) : m_name(name), m_colorName(colorName) {}
    ~Person() {}

    std::string getName() const { return m_name; }
    Color getColorName() const { return m_colorName; }
    void setName(std::string name) { m_name = name; }
    void setColorName(Color colorName) { m_colorName = colorName; }
};

class Message {
private:
    Person m_person;
    std::string m_content;
public:
    Message() {}
    Message(Person person, std::string content) : m_person(person), m_content(content) {}
    ~Message() {}

    Person getPerson() const { return m_person; }
    std::string getContent() const { return m_content; }

    void setPerson(Person person) { m_person = person; }
    void setContent(std::string content) { m_content = content; }
};

class Dialog {
private:
    std::queue<Message> m_messages;
public:
    // Constructors & Destructor
    Dialog();
    Dialog(std::queue<Message> msgs);
    ~Dialog();

    // Getters
    std::queue<Message>& getMessages();

    // Setters
    void setMessages(std::queue<Message> msgs);

    // Methods
    void addMessage(Message msg);
    void displayBorders(int topY, int bottomY);
    void displayBordersPers(int X, int X2,int Y, int Y2);
    void displayMessage();
    void displayMessResultHyp(int X,int Y);
    void displayConversation();
    void displayHypothesisVerification(Script solution, Script hypothesis);

};


#endif // DIALOG_H_INCLUDED
