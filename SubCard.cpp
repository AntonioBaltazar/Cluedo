#include <iostream>
#include "Card.h"
#include <vector>
#include <time.h>
#include "Utils.h"

///Create a package of cards and shuffle them
std::vector<Card> card_shuffle()
{
    std::vector<Card> MyPackage;
    std::vector<Card> MyPackageMixed;
    Card temp;

    srand(time(NULL));

    ///Creation of cards

    //Weapons cards
     MyPackage.push_back( Card("weapon","pistolet") );
     MyPackage.push_back( Card("weapon","corde")    );
     MyPackage.push_back( Card("weapon","matraque") );

    //Rooms cards
     MyPackage.push_back( Card("planet","Sature")   );
     MyPackage.push_back( Card("planet","Uranus")   );
     MyPackage.push_back( Card("planet","Venus")    );
     MyPackage.push_back( Card("planet","Soleil")   );

    //Suspects cards
     MyPackage.push_back( Card("person","emma")     );
     MyPackage.push_back( Card("person","martin")   );
     MyPackage.push_back( Card("person","tonio")    );

     //Shuffle algorithm
     for(int i = 0; i < NBCARDS -1; i++)
     {
        int random = rand()%NBCARDS;

        temp = MyPackage[i];
        MyPackageMixed.push_back(MyPackage[random]);
        MyPackage[random] = temp;
     }

    return MyPackageMixed;
}

///Displays every card of the package
void card_package_display(std::vector<Card> MyPackage)
{
    std::vector<Card>::iterator it;

    //
    for(it = MyPackage.begin(); it != MyPackage.end(); it++)
    {
        std::cout << color(it->getName(),Color::Blue);
        std::cout << color(it->getType(),Color::Green);
    }
}
