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


void Game::start3()
{
    getPlayers().push_back(Player("Martin", Color::Bright_Green, 14, 11, ""));
    getPlayers().push_back(Player("Emma", Color::Bright_Yellow, 16,12, ""));

    setAllPackages();
    cardDistrib();

    setSolution();

    getPlayers()[0].setHypothesis(getAllCard());

    //displaySolution();
    //getPlayers()[0].getHypothesis().display();

//    HypothesisVerification(getPlayers()[0]);

    //getPlayers()[0].show_card();
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

///Verify if the hypothesis made by a player is wrong or right and display the result
void Game::HypothesisVerification(Player p, bool finalPlace)
{
    Dialog d;
    Person mess;
    std::string text[2];
    bool right = false;

    if(finalPlace)
    {
        text[0]="Bravo ! Vous avez resolu l'enigme !";
        text[1]="Helas ce n'est pas la bonne reponse, vous avez perdu !";

    }else
    {
        text[0]="Vous pourriez peut-etre vous rendre a la case principale ?";
        text[1]="Peut-etre la prochaine fois !";
    }



    if( (p.getHypothesis().getPerson() == getSolution().getPerson()) && (p.getHypothesis().getRoom() == getSolution().getRoom()) && (p.getHypothesis().getWeapon() == getSolution().getWeapon()) )
      {
        d.addMessage(Message(mess,text[0]));
        right = true;
      }
    else
        d.addMessage(Message(mess,text[1]));

    if((text[0]=="Vous pourriez peut-etre vous rendre a la case principale ?" && right == true)
       || (text[1] == "Helas ce n'est pas la bonne reponse, vous avez perdu !" && right == false))
    {
        d.displayBordersPers(20,100,10,16);
        d.displayMessResultHyp(20,10,true);
    }else
    {
        d.displayBordersPers(35,85,10,16);
        d.displayMessResultHyp(35,10,false);
    }

    ///NE PAS OUBLIER DE MODIFIER addmessage dans displayMessResult DIALOGUE.CPP


    //Joueur dans la zone finale
   /* if(p.getX()>=ZONE X1 && p.getX()<= ZONE X2 && p.getY()>=ZONE Y1 && p.getY()<= ZONE Y2)
      {
        text[0]="Votre hypothese est bonne !";
        text[1]="Votre hypothese est fausse !";
      }
      else
      {
        text[0]="Vous pourriez peut-etre vous rendre à la case principale ?";
        text[1]="Peut-etre la prochaine fois !";
      }

   */


    while(!kbhit());
    getch();
    system("CLS");
}
