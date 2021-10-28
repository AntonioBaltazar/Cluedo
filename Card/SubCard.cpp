#include <iostream>
#include <vector>
#include <time.h>

#include "Card.h"
#include "Utils.h"


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
    myPackage.push_back( Card("person","emma")     );
    myPackage.push_back( Card("person","Martin")   );
    myPackage.push_back( Card("person","Tonio")    );

    return myPackage;
}

///Shuffle a package of cards
std::vector<Card> card_Shuffle(std::vector<Card> myPackage)
{
    Card temp;

    srand(time(NULL));

    int alea = rand()%(30 - 15 + 1) + 15;
    std::cout<<"Alea = "<<alea<<std::endl;

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
        std::cout << color(it->getType(),Color::Blue);
        std::cout <<" "<< color(it->getName(),Color::Green)<<std::endl;
    }
}


///Optionnal
void card_Management()
{
    std::vector<Card> myPackage;

    myPackage = card_Creation(); //Mélange
    myPackage = card_Shuffle(myPackage); //Mélange
    card_Package_Display(myPackage); //Affichage
}
