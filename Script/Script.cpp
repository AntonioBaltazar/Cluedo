#include "Script.h"
#include "iostream"
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

///Manage all the subprograms concerning the script, the hypothesis and the card package
void script_management()
{
    int nb_card = 0;
    Player p;
    Card temp;
    system("CLS");

    /// Card package creation and shuffle
    std::vector<Card> myPackage = temp.card_Creation(nb_card);
    myPackage = temp.card_Shuffle(myPackage, nb_card);

    p.create_player_package(myPackage);
    Script solution;
    Script hypothesis;
    /// Script creation
    solution.script_Creation(myPackage);
    solution.display();

    /// Player makes an hypothesis
    hypothesis.make_hypothesis(myPackage,false);
    hypothesis.display();
    /// We compare the solution and the hypothesis and display the result
    //HypothesisVerification(solution,hypothesis);

    ///Player p shows a card
    //show_card();

    gotoxy(0,23);

}

///Create the solution of the murderer and returns it in a script
void Script::script_Creation(std::vector<Card> myPackage)
{
    Script solution;
    std::vector<Card>::iterator it;

    for(it = myPackage.begin();  it != myPackage.end() ; it++ )
    {
        //Test if it is a person card, if yes we set this person as the murderer of Mr Lenoir
        if(it->getType() == "Person")
            setPerson(it->getName());

        //Test if it is a room card, if yes we set this room as the place of the murder of Mr Lenoir
        if(it->getType() == "Planet")
            setRoom(it->getName());

        //Test if it is a weapon card, if yes we set this weapon as the object that was used for the murder
        if(it->getType() == "Weapon")
            setWeapon(it->getName());
    }
}


void Script::display() { std::cout<<m_person<<" a tue Mr Lenoir sur "<<m_room<<" avec "<<m_weapon<<std::endl; }


/// Allow the player to make an hypothesis and returns it
void Script::make_hypothesis(std::vector<Card> myPackage, bool finalHypothesis)
{
    Script hypothesis("quelqu'un","une planete","quelque chose");
    Person accuser("Accuseur",Color::Red);
    int column = 0;
    int key = 0;
    int x = 18;
    int y = 8;
    int choice = 0;

    system("cls");

    ///Display all choices possible
    std::vector<Card> hyPackage = display_tab_hyp(hypothesis,myPackage, accuser);

    gotoxy(x,y);
    std::cout<<char(16);
    while(column<3)
    {
        hypothesis = choose_elem(hyPackage,choice, column, hypothesis);

        gotoxy(20,23);
        std::cout<<color(accuser.getName()+" : ",accuser.getColorName());
        gotoxy(23+accuser.getName().size(),23);
        std::cout<<"Mr Lenoir a ete tue par "<<color(hypothesis.getPerson(),Color::Yellow);
        std::cout<<" sur "<<color(hypothesis.getRoom(),Color::Blue);
        std::cout<<" avec "<<color(hypothesis.getWeapon(),Color::Magenta)<<".       ";

        key = getInput();

        gotoxy(x,y);
        std::cout<<" ";

        if (key == 72 && choice > 0) {  y = y-2;    choice--;   }

        if (key == 80 && choice < 5) {  y = y+2;    choice++;   }

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
std::vector<Card> Script::display_tab_hyp(Script hypothesis,std::vector<Card> myPackage, Person accuser)
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

    std::vector<Card> hyPackage = display_elem_tab_hyp(myPackage);

    return hyPackage;
}


///Display the elements of all cards in our hypothesis tab
std::vector<Card> Script::display_elem_tab_hyp(std::vector<Card> myPackage)
{
    int cmptPerson = 8, cmptRoom = 8, cmptWeapon = 8;
    int i=0, j=6, k=12;
    std::vector<Card>::iterator it;
    std::vector<Card> temp;
    Card hyPackage[18];

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

    for(int m = 0; m < 18; m++)
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
        switch(choice)
        {
        case 0: i = 0;   break;
        case 1: i = 1;   break;
        case 2: i = 2;   break;
        case 3: i = 3;   break;
        case 4: i = 4;   break;
        case 5: i = 5;   break;
        }
        hypothesis.setPerson(hyPackage[i].getName());
        hypothesis.setRoom(prev.getRoom());
        hypothesis.setWeapon(prev.getWeapon());
    }

    if(column == 1)
    {
        switch(choice)
        {
        case 0: i = 6;   break;
        case 1: i = 7;   break;
        case 2: i = 8;   break;
        case 3: i = 9;   break;
        case 4: i = 10;   break;
        case 5: i = 11;   break;
        }
        hypothesis.setPerson(prev.getPerson());
        hypothesis.setRoom(hyPackage[i].getName());
        hypothesis.setWeapon(prev.getWeapon());
    }

    if(column == 2)
    {
        switch(choice)
        {
        case 0: i = 12;   break;
        case 1: i = 13;   break;
        case 2: i = 14;   break;
        case 3: i = 15;   break;
        case 4: i = 16;   break;
        case 5: i = 17;   break;
        }
        hypothesis.setPerson(prev.getPerson());
        hypothesis.setRoom(prev.getRoom());
        hypothesis.setWeapon(hyPackage[i].getName());
    }
    return hypothesis;
}

