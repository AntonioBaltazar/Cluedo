#ifndef DIALOG_H_INCLUDED
#define DIALOG_H_INCLUDED

#include <queue>

class Person {
private:
    std::string m_name;
public:
    Person() {}
    Person(std::string name) : m_name(name) {}
    ~Person() {}

    std::string getName() const { return m_name; }
    void setName(std::string name) { m_name = name; }
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
    void displayMessage();

};


#endif // DIALOG_H_INCLUDED
