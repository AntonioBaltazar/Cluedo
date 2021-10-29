#include "Script.h"
#include "../Card/Card.h"
#include <vector>
#include <time.h>
#include <iostream>
void script_Creation()
{
    Script myScript;
    std::vector<Card> myPackage = card_Creation();

    card_Package_Display(myPackage);

    srand(time(NULL));

    int aleaPerson = rand()%SUSPECTS;
    int aleaRoom = rand()%ROOM;
    int aleaWeapon = rand()%WEAPON;

    ///Test if it is a person card, if yes we set this person as the murderer of Mr Lenoir
    do
    {
        aleaPerson = rand()%SUSPECTS;
        std::cout<<"suspects\n";
    }while(myPackage[aleaPerson].getType()!="person");

        std::cout<<"aleaRoom = "<<aleaWeapon<<std::endl;
    myScript.setPerson((myPackage[aleaPerson].getName()));

    ///Test if it is a room card, if yes we set this room as the place of the murder of Mr Lenoir
    do
    {
        aleaRoom = rand()%ROOM;
    }while(myPackage[aleaRoom].getType()!="planet");

    std::cout<<"aleaRoom = "<<aleaRoom<<std::endl;
    myScript.setRoom((myPackage[aleaRoom].getName()));

    ///Test if it is a weapon card, if yes we set this weapon as the object that was used for the murder
    do
    {
        aleaWeapon = rand()%WEAPON;
    }while(myPackage[aleaWeapon].getType()!="weapon");

    std::cout<<"aleaWeapon = "<<aleaWeapon<<std::endl;
    myScript.setWeapon((myPackage[aleaWeapon].getName()));

    myScript.display();


    //myPackage.display();

    //Creer une génération aléatoire de scénario donc inclure le paquet de cartes puis tirer un élément aléatoire a chaque fois

}
