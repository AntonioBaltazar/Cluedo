#include <iostream>
#include <windows.h>
#include <conio.h>

#include "../render/Dice.h"
#include "../Utils.h"
#include "../Card/Card.h"
#include "../Script/Script.h"
#include "../ConsoleHandler.h"
#include "../Game.h"
#include "../scenes/Menu.h"


bool Game::handleHypothesis(Player *p, Player nextP)
{
    int possibilities = 0;
    bool finish = false;

    ///*************************************************************************
    gotoxy(5,23);
    getSolution().display();

    while(!kbhit());
    getch();
    ///*************************************************************************

    CanMakeHypothesis(*p);

    possibilities = p->getCanMakeHypothesis();

    if(possibilities == 0)
        return false;
    else
    {
        p->setHypothesis(getAllCard());


        if(possibilities == 1)
        {
            HypothesisVerification(*p,false);

            nextP.show_card();
        }

        else if(possibilities == 2)
        {
            finish = HypothesisVerification(*p,true);
            p->setCanPlay(finish);
        }

        return finish;
    }


}


void Game::CanMakeHypothesis(Player &p)
{
    //Player can make the final accusation
    if(p.getX()>13 && p.getX()<21 && p.getY()>10 && p.getY()<13 && p.getWorldName() == "maps/main")
        p.setCanMakeHypothesis(2);
    else if(p.getWorldName()!="maps/main")
        p.setCanMakeHypothesis(1);
    else
        p.setCanMakeHypothesis(0);
}

void Game::setSolution()
{
    m_solution.script_Creation(getAllCard());
}

Script Game::getSolution() const  { return m_solution; }

void Game::displaySolution()
{
    getSolution().display();
}

///Verify if the hypothesis made by a player is wrong or right and display the result. Also returns true if the player made the righ accusation
bool Game::HypothesisVerification(Player &p, bool finalPlace)
{
    Dialog d;
    Person mess;
    std::string text[2];
    bool right = false;
    bool isGameOver = false;

    if(finalPlace)
    {
        text[0]="Bravo ! Vous avez r\x82solu l'\x82nigme !";
        text[1]="H\x82las ce n'est pas la bonne r\x82ponse, vous avez perdu !";

    }else
    {
        text[0]="Vous pourriez peut-\x88tre vous rendre \x85 la case principale ?";
        text[1]= "En \x88tes vous sur ?";
    }

    if( (p.getHypothesis().getPerson() == getSolution().getPerson()) && (p.getHypothesis().getRoom() == getSolution().getRoom()) && (p.getHypothesis().getWeapon() == getSolution().getWeapon()) )
      {
        d.addMessage(Message(mess,text[0]));
        right = true;
        if(finalPlace)
            isGameOver = true;
      }
    else
        d.addMessage(Message(mess,text[1]));

    if((text[0]=="Vous pourriez peut-\x88tre vous rendre \x85 la case principale ?" && right == true)
       || (text[1] == "H\x82las ce n'est pas la bonne r\x82ponse, vous avez perdu !" && right == false))
    {
        d.displayBordersPers(20,100,10,16);
        d.displayMessResultHyp(20,10,true);
    }
    else if(text[1]=="En \x88tes vous sur ?")
    {
        d.displayBordersPers(35,85,10,16);
        d.displayMessResultHyp(40,10,false);
    }
    else
    {
        d.displayBordersPers(35,85,10,16);
        d.displayMessResultHyp(32,10,false);
    }

    while(!kbhit());
    getch();
    system("CLS");

    return isGameOver;
}
