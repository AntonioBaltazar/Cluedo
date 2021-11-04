#ifndef SCRIPT_H_INCLUDED
#define SCRIPT_H_INCLUDED

#include <string>
#include "../Card/Card.h"

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

    ///Setter
     void setPerson(std::string person);
     void setRoom(std::string room);
     void setWeapon(std::string weapon);

    ///Methods
    void display();
};

void script_Creation();
Script make_hypothesis(std::vector<Card> myPackage);
void display_tab_hyp(Script hypothesis,std::vector<Card> myPackage);
void display_elem_tab_hyp(std::vector<Card> myPackage);
void HypothesisVerification(Script solution, Script hypothesis);

#endif // SCRIPT_H_INCLUDED
