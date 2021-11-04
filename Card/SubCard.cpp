#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>

#include "Card.h"
#include "../Utils.h"


///Read file "CHANGEME.txt" and create a card package depending on the information of the file that will be returned
std::vector<Card> card_Creation()
{
    std::string content;
    std::string path = "CHANGEME.txt";
    std::ifstream file(path.c_str());
    std::vector<Card> myPackage;

    if(file) //If the file was well opened then we recover the information
    {
        while(std::getline(file,content))
            if(content != "")
                myPackage.push_back(card_convert(content));


        file.close();
    }else //if not we warn the user
    {
        std::cout << "Cannot read " << path << std::endl;
    }

    return myPackage;
}


///Get a string wich represents a line of the file CHANGEME.txt and create a card that will be returned
Card card_convert(std::string content)
{
    Card newCard;
    std::vector <std::string> newContent;

    newContent = strSplit(content," : ");

    newCard.setType(newContent[0]);
    newCard.setName(newContent[1]);

    return newCard;
}


///Shuffle a package of cards
std::vector<Card> card_Shuffle(std::vector<Card> myPackage)
{
    Card temp;

    srand(time(NULL));

    //Shuffle algorithm
    for(int i = 0; i < 15; i++)
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
Card card_pick(std::vector<Card> &myPackage)
{
    Card temp ;
    auto picked_elem = myPackage.end()-1;

    temp.setType(picked_elem->getType());
    temp.setName(picked_elem->getName());

    myPackage.erase(picked_elem);

    return temp;

}


///Optionnal
void card_Management()
{
    std::vector<Card> myPackage;

    myPackage = card_Creation(); //Mélange
    myPackage = card_Shuffle(myPackage); //Mélange
    card_Package_Display(myPackage); //Affichage

    std::cout<<"Creation, Shuffle and display over\n";
    Card pioche;

    pioche = card_pick(myPackage);
    card_Package_Display(myPackage);

}


