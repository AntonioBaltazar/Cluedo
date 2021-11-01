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
    Script guess;
    std::vector<Card> myPackage = card_Creation();
    std::vector<Card>::iterator it;

    guess.setPerson("Jean");
    guess.setRoom("Jean");
    guess.setWeapon("Jean");
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

    hypothesis_verification(myScript,guess);

    //std::cout<<"Mr Lenoir was killed by "<<myScript.getPerson()<<" with a "<<myScript.getWeapon()<<" in "<<myScript.getRoom()<<std::endl;
}

///Verify if the hypothesis made by a player is correct, and diplsay the answer
void hypothesis_verification(Script solution, Script hypothesis)
{
    bool correct;
    Person p("Cluedo",Color::Blue);
    Message correct_answer(p,"Your guess is right !");
    Message wrong_answer(p,"Your guess is wrong !");

    Dialog chat;

    if( (hypothesis.getPerson() == solution.getPerson()) && (hypothesis.getRoom() == solution.getRoom()) && (hypothesis.getWeapon() == solution.getWeapon()) )
        chat.addMessage(Message(p,"Your guess is right !"));
    else
        chat.addMessage(Message(p,"Your guess is wrong !"));

    chat.displayConversation();
}
