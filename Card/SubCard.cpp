#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>

#include "Card.h"
#include "../Utils.h"


std::vector<Card> card_CreationB()
{
    std::string content;
    std::string path = "CHANGEME.txt";
    std::ifstream file(path.c_str());
    std::vector<Card> myPackage;

    if(file)
    {
        while(std::getline(file,content))
        {
            std::cout<<content<<std::endl;
            myPackage.push_back(card_CreationC(content));
        }

        std::cout << "Reading " << path << " => OK" << std::endl;
        file.close(); // fermeture du flux
    }else // en cas d'erreur...
    {
        std::cout << "Cannot read " << path << std::endl;
    }

    return myPackage;
}

Card card_CreationC(std::string content)
{
    Card newCard;
    std::vector <std::string> newContent;
    //int i = 0;

    newContent = strSplit(content," : ");

    if(newContent[0] == "Personnage")
    {
        ///On set les infos
    }



    return newCard;
}


/// COMMMENTAIRE A RETIRER : subscript (decla de myPackage)

/*
///Creation of a card package
std::vector<Card> card_Creation()
{
    std::vector<Card> myPackage;


    //Weapons cards
    myPackage.push_back( Card("weapon","pistolet") );
    myPackage.push_back( Card("weapon","corde")    );
    myPackage.push_back( Card("weapon","matraque") );

    //Rooms cards
    myPackage.push_back( Card("planet","Saturne")   );
    myPackage.push_back( Card("planet","Uranus")   );
    myPackage.push_back( Card("planet","Venus")    );
    myPackage.push_back( Card("planet","Soleil")   );

    //Suspects cards
    myPackage.push_back( Card("person","Emma")     );
    myPackage.push_back( Card("person","Martin")   );
    myPackage.push_back( Card("person","Tonio")    );

    return myPackage;
}
*/

///Shuffle a package of cards
std::vector<Card> card_Shuffle(std::vector<Card> myPackage)
{
    Card temp;

    srand(time(NULL));
    int alea = rand()%(30 - 15 + 1) + 15;

    //Shuffle algorithm
    for(int i = 0; i < alea; i++)
    {
        int random1 = 0, random2 = 0;
        do
        {
            random1 = rand()%NBCARDS;
            random2 = rand()%NBCARDS;
        }
        while(random1 == random2);

        temp = myPackage[random1];
        myPackage[random1] = myPackage[random2];
        myPackage[random2] = temp;
    }
    return myPackage;
}

///Displays every card of the package
void card_Package_Display(std::vector<Card> myPackage)
{
    std::vector<Card>::iterator it;

    for(it = myPackage.begin(); it != myPackage.end(); it++)
    {
        if(it->getType()=="person")
        {
            std::cout << color(it->getType(),Color::Blue);
            std::cout <<" "<< color(it->getName(),Color::Bright_Blue)<<std::endl;
        }

        if(it->getType()=="planet")
        {
            std::cout << color(it->getType(),Color::Red);
            std::cout <<" "<< color(it->getName(),Color::Bright_Red)<<std::endl;
        }

        if(it->getType()=="weapon")
        {
            std::cout << color(it->getType(),Color::Green);
            std::cout <<" "<< color(it->getName(),Color::Bright_Green)<<std::endl;
        }
    }
}


///Optionnal
void card_Management()
{
    std::vector<Card> myPackage;

    myPackage = card_CreationB(); //Mélange
    //myPackage = card_Shuffle(myPackage); //Mélange
    //card_Package_Display(myPackage); //Affichage
}
