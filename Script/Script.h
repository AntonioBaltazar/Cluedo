#ifndef SCRIPT_H_INCLUDED
#define SCRIPT_H_INCLUDED

#include <string>

class Script
{
private :
    std::string m_person;
    std::string m_room;
    std::string m_weapon;
public:
    ///Constructor and Destructor
    Script();
    Script(std::string person, std::string room, std::string weapon);
    ~Script();

    ///Getter
    std::string getPerson()const;
    std::string getRoom()const;
    std::string getWeapon()const;

    ///Methods
    void display();
};

#endif // SCRIPT_H_INCLUDED
