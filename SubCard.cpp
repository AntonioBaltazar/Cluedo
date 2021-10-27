#include <iostream>
#include "Card.h"
#include <vector>
#include <time.h>
#include "Utils.h"

///Creation of a card package
std::vector<Card> card_creation()
{
    std::vector<Card> MyPackage;
    //Weapons cards
    MyPackage.push_back( Card("weapon","pistolet") );
    MyPackage.push_back( Card("weapon","corde")    );
    MyPackage.push_back( Card("weapon","matraque") );

    //Rooms cards
    MyPackage.push_back( Card("planet","Saturne")   );
    MyPackage.push_back( Card("planet","Uranus")   );
    MyPackage.push_back( Card("planet","Venus")    );
    MyPackage.push_back( Card("planet","Soleil")   );

    //Suspects cards
    MyPackage.push_back( Card("person","emma")     );
    MyPackage.push_back( Card("person","Martin")   );
    MyPackage.push_back( Card("person","Tonio")    );

    return MyPackage;
}

///Shuffle a package of cards
std::vector<Card> card_shuffle(std::vector<Card> MyPackage)
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

        temp = MyPackage[random1];
        MyPackage[random1] = MyPackage[random2];
        MyPackage[random2] = temp;

    }

    return MyPackage;
}

///Displays every card of the package
void card_package_display(std::vector<Card> MyPackage)
{
    std::vector<Card>::iterator it;

    for(it = MyPackage.begin(); it != MyPackage.end(); it++)
    {
        std::cout << color(it->getType(),Color::Blue);
        std::cout <<" "<< color(it->getName(),Color::Green)<<std::endl;
    }
}


///Optionnal
void card_management()
{
    std::vector<Card> MyPackage;

    MyPackage = card_creation(); //M�lange
    MyPackage = card_shuffle(MyPackage); //M�lange
    card_package_display(MyPackage); //Affichage
}
