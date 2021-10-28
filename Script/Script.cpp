#include "Script.h"
#include "iostream"

//Constructor's and Destructor's Implementation

Script::Script()
     : m_person("Default Person"), m_room("Default room"), m_weapon("Default weapon")   {}

Script::Script(std::string person, std::string room, std::string weapon)
     : m_person(person), m_room(room), m_weapon(weapon)   {}

Script::~Script()   {}


///Getter's Implementation

std::string Script::getPerson()const  { return m_person ; }

std::string Script::getRoom()const    { return m_room ; }

std::string Script::getWeapon()const  { return m_weapon ; }


///Method's implementation

void Script::display() { std::cout<<m_person<<" killed Mr Lenoir in "<<m_room<<" with a "<<m_weapon<<std::endl; }
