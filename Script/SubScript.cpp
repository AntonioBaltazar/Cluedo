#include "Script.h"
#include "../Card/Card.h"
#include "../Utils.h"
#include "../Dialog.h"

#include <vector>
#include <time.h>
#include <iostream>
#include <conio.h>

///Manage all the subprograms concerning the script, the hypothesis and the card package
void script_management()
{
    /// Card package creation and shuffle
    std::vector<Card> myPackage = card_Creation();
    myPackage = card_Shuffle(myPackage);

    /// Script creation
    Script solution = script_Creation(myPackage);

    /// Player makes an hypothesis
    Script hypothesis = make_hypothesis(myPackage);

    /// We compare the solution and the hypothesis and display the result
    HypothesisVerification(solution,hypothesis);


}

///Create the solution of the murderer and returns it in a script
Script script_Creation(std::vector<Card> myPackage)
{
    Script solution;
    std::vector<Card>::iterator it;

    ///Test if it is a person card, if yes we set this person as the murderer of Mr Lenoir
    for(it = myPackage.begin();  it != myPackage.end() ; it++ )
        if(it->getType()== "Person")
            solution.setPerson(it->getName());


    ///Test if it is a room card, if yes we set this room as the place of the murder of Mr Lenoir
    for(it = myPackage.begin();  it != myPackage.end() ; it++ )
        if(it->getType()== "Planet")
            solution.setRoom(it->getName());

    ///Test if it is a weapon card, if yes we set this weapon as the object that was used for the murder
    for(it = myPackage.begin();  it != myPackage.end() ; it++ )
        if(it->getType()== "Weapon")
            solution.setWeapon(it->getName());

    return solution;
}

/// Allow the player to make an hypothesis and returns it
Script make_hypothesis(std::vector<Card> myPackage)
{
    Script hypothesis("Tonio","Venus","gun");
    Person accuser("Accuser",Color::Red);

    ///Display all choices possible
    display_tab_hyp(hypothesis,myPackage, accuser);

    ///Display the sentence of accusation
    gotoxy(20,23);
    std::cout<<color(accuser.getName()+" : ",accuser.getColorName());
    gotoxy(23+accuser.getName().size(),23);
    std::cout<<"Mr Lenoir was killed by "<<color(hypothesis.getPerson(),Color::Yellow);
    std::cout<<" in "<<color(hypothesis.getRoom(),Color::Blue);
    std::cout<<" with a "<<color(hypothesis.getWeapon(),Color::Magenta);

    while(!kbhit());
    getch();
    system("CLS");


    return hypothesis;
}

///Display a tab with all the card possible so that the player can make a choice
void display_tab_hyp(Script hypothesis,std::vector<Card> myPackage, Person accuser)
{
    Dialog d;
    int x1=5,x2=41,x3=77,x4=115;
    int y1=2,y2=6,y3=20;

    d.displayBordersPers(x1,x4,y1,y2);
    d.displayBordersPers(x1,x4,y2,y3);
    d.displayBordersPers(x1,x2,y1,y3);
    d.displayBordersPers(x2,x3,y1,y3);

    display_ansi(x1,y2,204);
    display_ansi(x4,y2,185);
    display_ansi(x2,y2,206);
    display_ansi(x3,y2,206);
    display_ansi(x3,y1,203);
    display_ansi(x2,y1,203);
    display_ansi(x3,y3,202);
    display_ansi(x2,y3,202);

    gotoxy((x2+x1)/2-3,y2-y1);
    std::cout<<color("Person",Color::Yellow);
    gotoxy((x2+x3)/2-3,y2-y1);
    std::cout<<color("Planet",Color::Blue);
    gotoxy((x4+x3)/2-3,y2-y1);
    std::cout<<color("Weapon",Color::Magenta);

    display_elem_tab_hyp(myPackage);


}

///Display the elements of all cards in our hypothesis tab
void display_elem_tab_hyp(std::vector<Card> myPackage)
{
    int cmptPerson = 8, cmptRoom = 8, cmptWeapon = 8;
    std::vector<Card>::iterator it;

    for(it = myPackage.begin();it!=myPackage.end();it++)
    {
        if(it->getType()=="Person")
        {
            gotoxy(20,cmptPerson);
            std::cout<<color(it->getName(),Color::Yellow);
            cmptPerson = cmptPerson+2;
        }

        if(it->getType()=="Planet")
        {
            gotoxy(56,cmptRoom);
            std::cout<<color(it->getName(),Color::Blue);
            cmptRoom = cmptRoom+2;
        }

        if(it->getType()=="Weapon")
        {
            gotoxy(93,cmptWeapon);
            std::cout<<color(it->getName(),Color::Magenta);
            cmptWeapon = cmptWeapon+2;
        }
    }
}

///Verify if the hypothesis made by a player is wrong or right and display the result
void HypothesisVerification(Script solution, Script hypothesis)
{
    Person p;
    Dialog d;

    if( (hypothesis.getPerson() == solution.getPerson()) && (hypothesis.getRoom() == solution.getRoom()) && (hypothesis.getWeapon() == solution.getWeapon()) )
        d.addMessage(Message(p,"Your guess is right !"));
    else
        d.addMessage(Message(p,"Your guess is wrong !"));

    d.displayBordersPers(40,80,10,16);

    d.displayMessResultHyp(40,10);

    while(!kbhit());
    getch();
    system("CLS");
}
