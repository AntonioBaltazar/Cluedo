#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>
#include <conio.h>

#include "Card.h"
#include "../Utils.h"


/// *********************       Constructor's and destructor's implementation        *********************** ///

Card::Card()
     : m_type("Default Type"), m_name("Default Name")   {}

Card::Card(std::string type, std::string name)
     : m_type(type), m_name(name)   {}

Card::~Card()   {}


/// *********************       getter's implementation        *********************** ///

std::string Card::getType()const  { return m_type ; }

std::string Card::getName()const  { return m_name ; }


/// *********************       Setters's implementation        *********************** ///
void Card::setType(std::string type)  { m_type = type ; }

void Card::setName(std::string name)  { m_name = name ; }


        /// *********************       Method's implementation        *********************** ///

///Read file "CHANGEME.txt" and create a card package depending on the information of the file that will be returned
std::vector<Card> Card::card_Creation(int &nb_card)
{
    Card temp;
    std::string content;
    std::string path = "CHANGEME.txt";
    std::ifstream file(path.c_str());
    std::vector<Card> myPackage;

    if(file) //If the file was well opened then we recover the informations
    {
        std::string nb_card_str;
        std::getline(file, nb_card_str);
        std::vector<std::string> newContent = strSplit(nb_card_str," : ");
        nb_card = std::stoi(newContent[1]);

        while(std::getline(file,content))
            if(content != "")
                myPackage.push_back(temp.card_convert(content));

        file.close();
    }else //if not we warn the user
        std::cout << "Cannot read " << path << std::endl;

    return myPackage;
}


///Get a string wich represents a line of the file CHANGEME.txt and create a card that will be returned
Card Card::card_convert(std::string content)
{
    Card newCard;
    std::vector <std::string> newContent;

    newContent = strSplit(content," : ");

    newCard.setType(newContent[0]);
    newCard.setName(newContent[1]);

    return newCard;
}


///Shuffle a package of cards
std::vector<Card> Card::card_Shuffle(std::vector<Card> myPackage,int nb_card)
{
    Card temp;

    srand(time(NULL));

    //Shuffle algorithm
    for(int i = 0; i < 15; i++)
    {
        int random1 = 0, random2 = 0;
        do
        {
            random1 = rand()%nb_card;
            random2 = rand()%nb_card;
        }
        while(random1 == random2);

        temp = myPackage[random1];
        myPackage[random1] = myPackage[random2];
        myPackage[random2] = temp;
    }
    return myPackage;
}


///Displays every card of the package
void Card::card_Package_Display(std::vector<Card> myPackage)
{
    std::vector<Card>::iterator it;

    for(it = myPackage.begin(); it != myPackage.end(); it++)
    {
        if(it->getType()=="Person")
        {
            std::cout << color(it->getType(),Color::Blue);
            std::cout <<" "<< color(it->getName(),Color::Bright_Blue)<<std::endl;
        }

        if(it->getType()=="Planet")
        {
            std::cout << color(it->getType(),Color::Red);
            std::cout <<" "<< color(it->getName(),Color::Bright_Red)<<std::endl;
        }

        if(it->getType()=="Weapon")
        {
            std::cout << color(it->getType(),Color::Green);
            std::cout <<" "<< color(it->getName(),Color::Bright_Green)<<std::endl;
        }
    }
}


///Player picks a card and that card is removed from the package, returns the picked card
Card Card::card_pick(std::vector<Card> &myPackage,std::string type)
{
    Card temp ;
    std::vector<Card>::iterator it;
    std::vector<Card>::iterator it2;

    for(it = myPackage.begin(); it != myPackage.end(); it++)
    {
       if(it->getType()==type)
           it2 = it;
    }
    temp.setType(it2->getType());
    temp.setName(it2->getName());

    myPackage.erase(it2);

    //temp.card_Package_Display(myPackage);

    return temp;
}


///Displays the information of a single card
void Card::display()
{
    std::cout<<"Type : "<<getType()<<"  Name : "<<getName()<<std::endl;
}

///Optionnal
void Card::card_Management()
{
    std::vector<Card> myPackage;
    Card temp;
    Card pioche;
    int nb_card = 0;

    myPackage = temp.card_Creation(nb_card); //Mélange
    myPackage = temp.card_Shuffle(myPackage, nb_card); //Mélange
    //temp.card_Package_Display(myPackage); //Affichage

    pioche = card_pick(myPackage,"person");
    card_Package_Display(myPackage);
}





