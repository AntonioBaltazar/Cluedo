#include "Script.h"
#include "../Card/Card.h"
#include <vector>
#include <time.h>

void script_Creation()
{
    Script myScript;
    std::vector<Card> myPackage = card_Creation();

    card_Package_Display(myPackage);

    srand(time(NULL));

    int aleaPerson = rand()%SUSPECTS;
    int aleaRoom = rand()%ROOM;
    int aleaWeapon = rand()%WEAPON;

    ///tester si on a bien une carte de type person
    do
    {
        aleaPerson = rand()%SUSPECTS;
    }while(myPackage[aleaPerson].getName()="person")

    myScript.setPerson((myPackage[aleaPerson].getName()));


    //myPackage.display();

    //Creer une génération aléatoire de scénario donc inclure le paquet de cartes puis tirer un élément aléatoire a chaque fois

}
