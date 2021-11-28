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


void Game::handlePlayerTurn2(Player* p, Dice* d)
{
    for (auto& w : getWorlds())
        if (w.getPath() == p->getWorldName())
            getDashboard().renderTurn(p, w.getName());
    AnimatedElement ae;
    std::vector<Square> pWorld;
    ae.saveAsWorld(pWorld, std::string(p->getWorldName()));
    ae.init(std::string(p->getWorldName()));

    displayMap(*p, pWorld, ae);
    p->setMovementAvailable(d->throwing());
    for (auto& w : getWorlds())
        if (w.getPath() == p->getWorldName())
            getDashboard().renderTurn(p, w.getName());

    std::string dialog("");
    int saisie;
    do
    {

        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        saisie = getInput();

         if (saisie == 72 && p->canMoveTo(0, -1, pWorld)) movePlayerTo(0, -1, pWorld, p, getWorldFromPath(p->getWorldName()));
        else if (saisie == 80 && p->canMoveTo(0, 1, pWorld)) movePlayerTo(0, 1, pWorld, p, getWorldFromPath(p->getWorldName()));
        else if (saisie == 75 && p->canMoveTo(-1, 0, pWorld)) movePlayerTo(-1, 0, pWorld, p, getWorldFromPath(p->getWorldName()));
        else if (saisie == 77 && p->canMoveTo(1, 0, pWorld)) movePlayerTo(1, 0, pWorld, p, getWorldFromPath(p->getWorldName()));
        else if (saisie == 110 || saisie == 78) {
            handleNotepad(p);
            displayMap(*p, pWorld, ae); }

        //Hypothesis
        if(saisie == 104)
        {
            setFinish(handleHypothesis(p));
            p->setMovementAvailable(0);
        }


        if (dialog != "") {
            startDialog(dialog);
            dialog = "";
            displayMap(*p, pWorld, ae);
        }

    }
    while (p->getMovementAvailable() > 0);
}

bool Game::handleHypothesis(Player *p)
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
        p->setHypothesis(getGamePackage());

        if(possibilities == 1)
            HypothesisVerification(*p,false);

        else if(possibilities == 2)
        {
            finish = HypothesisVerification(*p,true);
            p->setCanPlay(finish);
        }

        return finish;
    }

}

void Game::start3()
{

    // Getting datas before launching new game
    /*
    askNbOfPlayers();
    askAccountOfPlayers();
    */

    //Card package creation and shuffle
    setAllPackages();

    //We create a new script for the game
    setSolution();
    //getSolution().display();

    //displayPackage(getAllCard());

    //Card distribution to all the players
    cardDistrib();


    system("cls");

    getPlayers().push_back(Player("Martin", Color::Bright_Green, 14, 11, ""));
    getPlayers().push_back(Player("Emma", Color::Bright_Yellow, 16,12, ""));
    getPlayers().push_back(Player("Tonio", Color::Bright_Magenta, 15,13, ""));

    World board(16, 11, "Board", "maps/main");
    for (auto& p : getPlayers())
        board.addPlayer(&p, false);
    std::vector<World> wrlds = {World(16, 11, "Board", "maps/main"), World(18, 9, "Mars2", "maps/planets/mars"),
                                World(18, 9, "Jupiter2", "maps/planets/jupiter"), World(18, 9, "Earth2", "maps/planets/earth"),
                                World(18, 9, "Mercury2", "maps/planets/mercury"), World(18, 9, "Neptun2", "maps/planets/neptun"),
                                World(18, 9, "Saturn2", "maps/planets/saturn"), World(18, 9, "Venus2", "maps/planets/venus")};
    addWorld(board);
    for (auto& wrl : wrlds)
        addWorld(wrl);

    // Beginning
    Dice d(2, 1, 12, 6);
    //Dashboard db(100, 4, 25, 14);
    Dashboard db(94, 4, 25, 18);
    getDashboard() = db;
    Notepad np(2, 25, 25, 3);
    np.renderTurn();

    getElements().push_back(&d);
    getElements().push_back(&db);
    getElements().push_back(&np);

    int nbTurn = 0;
    while(!isFinish())
    {

        if(getPlayers()[nbTurn % getPlayers().size()].getCanPlay())
            handlePlayerTurn2(&getPlayers()[nbTurn % getPlayers().size()], &d);


        nbTurn++;
    }


    //getPlayers()[0].show_card();
//*/
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
