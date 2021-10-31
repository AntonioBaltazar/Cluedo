#include "Card.h"
#include <iostream>

///Constructor's and Destructor's Implementation

Card::Card()
     : m_type("Default Type"), m_name("Default Name")   {}

Card::Card(std::string type, std::string name)
     : m_type(type), m_name(name)   {}

Card::~Card()   {}


///Getter's Implementation

std::string Card::getType()const  { return m_type ; }

std::string Card::getName()const  { return m_name ; }

///Getter's Implementation
void Card::setType(std::string type)  { m_type = type ; }

void Card::setName(std::string name)  { m_name = name ; }

///Method's implementation

void Card::display()
{
    std::cout<<"Type : "<<m_type<<std::endl;
    std::cout<<"Name : "<<m_name<<std::endl;
}



