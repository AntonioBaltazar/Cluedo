#include "Script.h"
#include "../Card/Card.h"
#include "../Utils.h"
#include "../Dialog.h"

#include <vector>
#include <time.h>
#include <iostream>


void script_Creation()
{
    Script myScript;
    std::vector<Card> myPackage = card_Creation();
    std::vector<Card>::iterator it;

    myPackage = card_Shuffle(myPackage);

    ///Test if it is a person card, if yes we set this person as the murderer of Mr Lenoir
    for(it = myPackage.begin();  it != myPackage.end() ; it++ )
        if(it->getType()== "Person")
            myScript.setPerson(it->getName());


    ///Test if it is a room card, if yes we set this room as the place of the murder of Mr Lenoir
    for(it = myPackage.begin();  it != myPackage.end() ; it++ )
        if(it->getType()== "Planet")
            myScript.setRoom(it->getName());

    ///Test if it is a weapon card, if yes we set this weapon as the object that was used for the murder
    for(it = myPackage.begin();  it != myPackage.end() ; it++ )
        if(it->getType()== "Weapon")
            myScript.setWeapon(it->getName());

    /// ******** Utilisé uniquement pour des tests ********* ///
    Script jsp;
    Dialog d;
    d.displayHypothesisVerification(myScript,jsp );

    //std::cout<<"Mr Lenoir was killed by "<<myScript.getPerson()<<" with a "<<myScript.getWeapon()<<" in "<<myScript.getRoom()<<std::endl;
}
