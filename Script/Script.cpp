#include "Script.h"
#include <iostream>
#include <time.h>
#include "../Player.h"
//Constructor's and Destructor's Implementation
///     **********       Constructor's and Destructor's IMPLEMENTATION     ****************        ///
Script::Script()
     : m_person("Default Person"), m_room("Default room"), m_weapon("Default weapon")   {}

Script::Script(std::string person, std::string room, std::string weapon)
     : m_person(person), m_room(room), m_weapon(weapon)   {}

Script::~Script()   {}


        ///     *********************      GETTER'S IMPLEMENTATION     ****************************        ///

std::string Script::getPerson()const  { return m_person ; }

std::string Script::getRoom()const    { return m_room ; }

std::string Script::getWeapon()const  { return m_weapon ; }


    ///     *********************       SETTER'S IMPLEMENTATION     ****************************        ///

void Script::setPerson(std::string person)  { m_person=person ; }

void Script::setRoom(std::string room)      { m_room=room ; }

void Script::setWeapon(std::string weapon)  { m_weapon=weapon ; }

        ///     *********************       METHOD'S IMPLEMENTATION     ****************************        ///

///Create the solution of the murderer and returns it in a script
void Script::script_Creation(std::vector<Card> myPackage)
{
    Script solution;
    std::vector<Card>::iterator it;
    std::vector<Card> person;
    std::vector<Card> planet;
    std::vector<Card> weapon;
    int random = 0;

    srand(time(NULL));

    for(it = myPackage.begin();  it != myPackage.end() ; it++ )
    {
        //Test if it is a person card, if yes we set this person as the murderer of Mr Lenoir
        if(it->getType() == "Person")
            person.push_back(Card(it->getType(), it->getName()));

        //Test if it is a room card, if yes we set this room as the place of the murder of Mr Lenoir
        if(it->getType() == "Planet")
            planet.push_back(Card(it->getType(), it->getName()));

        //Test if it is a weapon card, if yes we set this weapon as the object that was used for the murder
        if(it->getType() == "Weapon")
            weapon.push_back(Card(it->getType(), it->getName()));
    }

    random=rand()%person.size();
    setPerson(person[random].getName());

    random=rand()%planet.size();
    setRoom(planet[random].getName());

    random=rand()%weapon.size();
    setWeapon(weapon[random].getName());
}


void Script::display() { std::cout<<m_person<<" a tue Mr Lenoir sur "<<m_room<<" avec "<<m_weapon<<std::endl; }

/// Allow the player to make an hypothesis and returns it
void Script::make_hypothesis(std::vector<Card> myPackage, bool finalHypothesis, std::string name, Color playerColor, std::string planete)
{
    Script hypothesis("quelqu'un","une plan\x8a\te","quelque chose");
    int column = 0;
    int key = 0;
    int x = 18;
    int y = 8;
    int choice = 0;
    system("cls");

    ///Display all choices possible
    std::vector<Card> hyPackage = display_tab_hyp(hypothesis,myPackage);

    gotoxy(x,y);
    std::cout<<char(16);
    while(column<3)
    {
        hypothesis = choose_elem(hyPackage,choice, column, hypothesis);

        gotoxy(20,23);
        std::cout<<color(name+" : ",playerColor);
        gotoxy(23+name.size(),23);
        std::cout<<"Mr Lenoir a \x82t\x82 tu\x82 par "<<color(hypothesis.getPerson(),Color::Yellow);
        if(finalHypothesis)
        {
            std::vector<std::string> temp = strSplit(planete,"/");
            temp[2][0] -= 32;
            std::cout<<" sur "<<color(temp[2],Color::Blue);
        }
        else
            std::cout<<" sur "<<color(hypothesis.getRoom(),Color::Blue);

        std::cout<<" avec "<<color(hypothesis.getWeapon(),Color::Magenta)<<".       ";

        key = getInput();

        gotoxy(x,y);
        std::cout<<" ";

        if (key == 72 && choice > 0) {  y = y-2;    choice--;   }

        if (key == 80 && choice < 6) {  y = y+2;    choice++;   }

        if(key == 13 && finalHypothesis == false)
            column++;

        if(key == 13 && finalHypothesis == true)
            column+=2;

        switch(column)
        {
        case 0 : x = 18; break;
        case 1 : x = 54; break;
        case 2 : x = 91; break;
        default: break;
        }
        gotoxy(x,y);
        std::cout<<char(16);
    }

    setPerson(hypothesis.getPerson());
    setRoom(hypothesis.getRoom());
    setWeapon(hypothesis.getWeapon());
    system("CLS");

}

///Display a tab with all the card possible so that the player can make a choice
std::vector<Card> Script::display_tab_hyp(Script hypothesis,std::vector<Card> myPackage)
{
    Dialog d;
    int x1=5,x2=41,x3=77,x4=115;
    int y1=2,y2=6,y3=22;

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

    std::vector<Card> hyPackage = display_elem_tab_hyp(myPackage);

    return hyPackage;
}


///Display the elements of all cards in our hypothesis tab
std::vector<Card> Script::display_elem_tab_hyp(std::vector<Card> myPackage)
{
    int cmptPerson = 8, cmptRoom = 8, cmptWeapon = 8;
    int i=0, j=7, k=14;
    std::vector<Card>::iterator it;
    std::vector<Card> temp;
    Card hyPackage[22];

    for(it = myPackage.begin();it!=myPackage.end();it++)
    {
        if(it->getType()=="Person")
        {
            gotoxy(20,cmptPerson);
            std::cout<<color(it->getName(),Color::Yellow);
            cmptPerson = cmptPerson+2;
            hyPackage[i].setName(it->getName());
            i++;
        }

        if(it->getType()=="Planet")
        {
            gotoxy(56,cmptRoom);
            std::cout<<color(it->getName(),Color::Blue);
            cmptRoom = cmptRoom+2;
            hyPackage[j].setName(it->getName());
            j++;
        }

        if(it->getType()=="Weapon")
        {
            gotoxy(93,cmptWeapon);

            std::string temp = it->getName();

            if(temp[0]=='u' && temp[1]=='n' && temp[2]==' ')
                for(int i = 3; temp[i]!='\0'; i++)
                    std::cout<<color(temp[i],Color::Magenta);

            else if(temp[0]=='u' && temp[1]=='n' && temp[2]=='e')
                for(int i = 4; temp[i]!='\0'; i++)
                    std::cout<<color(temp[i],Color::Magenta);

            else
                std::cout<<color(it->getName(),Color::Magenta);

            cmptWeapon = cmptWeapon+2;
            hyPackage[k].setName(it->getName());
            k++;
        }

    }

    for(int m = 0; m < 21; m++)
    {
        temp.push_back(hyPackage[m]);
    }

    return temp;
}


///Allows to select the elements of the accusation
Script Script::choose_elem(std::vector<Card> hyPackage, int choice, int column, Script prev)
{
    Script hypothesis;
    int i=0;

    if(column == 0)
    {
        i = choice;
        hypothesis.setPerson(hyPackage[i].getName());
        hypothesis.setRoom(prev.getRoom());
        hypothesis.setWeapon(prev.getWeapon());
    }

    if(column == 1)
    {
        i = choice +7;
        hypothesis.setPerson(prev.getPerson());
        hypothesis.setRoom(hyPackage[i].getName());
        hypothesis.setWeapon(prev.getWeapon());
    }

    if(column == 2)
    {
        i = choice +14;
        hypothesis.setPerson(prev.getPerson());
        hypothesis.setRoom(prev.getRoom());
        hypothesis.setWeapon(hyPackage[i].getName());
    }

    return hypothesis;
}

