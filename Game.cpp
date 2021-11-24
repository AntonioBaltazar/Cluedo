#include <iostream>
#include <windows.h>
#include <algorithm>
#include <conio.h>
#include <vector>
#include <fstream>
#include "World.h"
#include "render/Dice.h"
#include "Player.h"
#include "Game.h"
#include "AnimatedElement.h"
#include "Utils.h"
#include "Dashboard/Dashboard.h"

// Methods
void Game::addWorld(World w) {   getWorlds().push_back(w);  }

void Game::setNbCard( int nbCard)   { m_nbCard = nbCard; }
void Game::setGamePackage()
 {
    Card temp;
    int nbCard;
    m_gamePackage = temp.card_Creation(nbCard);
    m_gamePackage = temp.card_Shuffle(getGamePackage(),nbCard);
    setNbCard(nbCard);
 }

std::vector<Card> Game::getGamePackage()    {  return m_gamePackage;}

std::vector<Card> Game::createGamePackage() { setGamePackage(); return m_gamePackage;}

void Game::displayPackage(std::vector<Card> Gamepackage)
{
    Card temp;

    temp.card_Package_Display(Gamepackage);
}

void Game::start()
{
    // Getting datas before launching new game
    /*
    askNbOfPlayers();
    askAccountOfPlayers();
    */

    //Card package creation and shuffle
    setGamePackage();

    //Card distribution to all the players
    cardDistrib();

    system("cls");

    getPlayers().push_back(Player("Martin", Color::Bright_Green, 14, 11, ""));
    getPlayers().push_back(Player("Emma", Color::Bright_Yellow, 16,12, ""));

    World board(16, 11, "Board", "maps/main");
    for (auto& p : getPlayers())
        board.addPlayer(&p);
    std::vector<World> wrlds = {World(16, 11, "Board", "maps/main"), World(18, 9, "Mars2", "maps/planets/mars"),
                                World(18, 9, "Jupiter2", "maps/planets/jupiter"), World(18, 9, "Earth2", "maps/planets/earth"),
                                World(18, 9, "Mercury2", "maps/planets/mercury"), World(18, 9, "Neptun2", "maps/planets/neptun"),
                                World(18, 9, "Saturn2", "maps/planets/saturn"), World(18, 9, "Venus2", "maps/planets/venus")};
    addWorld(board);
    for (auto& wrl : wrlds)
        addWorld(wrl);

    ///Creer le packet de cartes

    ///Le m�langer

    ///Comme handlePlayerTurn, chaque jours pick une carte de chaque type


    ///J'aurai besoin de, un set card dans player, un create package dans Game.cpp

    // Beginning
    Dice d(2, 1, 12, 6);
    Dashboard db(90, 3, 25, 10);
    getDashboard() = db;

    getElements().push_back(d);
    getElements().push_back(db);

    int nbTurn = 0;
    while(!isFinish())
    {
        handlePlayerTurn(&getPlayers()[nbTurn % getPlayers().size()], &d);
        nbTurn++;
    }

    while(!kbhit());
}

void Game::handlePlayerTurn(Player* p, Dice* d)
{
    getDashboard().renderTurn(p);
    AnimatedElement ae;
    std::vector<Square> pWorld;
    ae.saveAsWorld(pWorld, std::string(p->getWorldName()));
    ae.init(std::string(p->getWorldName()));

    displayMap(*p, pWorld, ae);
    p->setMovementAvailable(d->throwing());

    std::string dialog("");
    int saisie;
    do
    {
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        saisie = getInput();

        if (saisie == 72 && p->canMoveTo(0, -1, pWorld)) dialog = movePlayerTo(0, -1, pWorld, p, getWorldFromPath(p->getWorldName()));
        if (saisie == 80 && p->canMoveTo(0, 1, pWorld)) dialog = movePlayerTo(0, 1, pWorld, p, getWorldFromPath(p->getWorldName()));
        if (saisie == 75 && p->canMoveTo(-1, 0, pWorld)) dialog = movePlayerTo(-1, 0, pWorld, p, getWorldFromPath(p->getWorldName()));
        if (saisie == 77 && p->canMoveTo(1, 0, pWorld)) dialog = movePlayerTo(1, 0, pWorld, p, getWorldFromPath(p->getWorldName()));
        if (dialog != "") {
            startDialog(dialog);
            dialog = "";
            displayMap(*p, pWorld, ae);
        }
    }
    while (p->getMovementAvailable() > 0);
}

void Game::displayMap(Player p, std::vector<Square> pWorld, AnimatedElement world)
{
    int realX = 60;
    int realY = 13;

    // Refreshing board
    clearGlobal();
    showStars(world, p);

    // Print for each element in the world
    for (const auto& el : pWorld)
        if ((realX - p.getX() + el.getX())%120 >= 0 && (realY - p.getY() + el.getY())%25 >= 0)
        {
            int x(realX - p.getX() + el.getX()), y(realY - p.getY() + el.getY());
            bool deleting = true;
            for (auto& anel : getElements())
                if (anel.getTranslatedX() <= x && x <= anel.getTranslatedX() + anel.getMaxX() &&
                        anel.getTranslatedY() <= y && y <= anel.getTranslatedY() + anel.getMaxY())
                {
                    deleting = false;
                    break;
                }
            if (deleting)
                printAt(x, y, color(el.getContent(), el.getColor()));
        }


    printAt(realX, realY, color(std::string(1, char(254)), p.getColorName()));
    // Print others players
    for (auto& pl : getPlayers())
        if (pl.getWorldName() == p.getWorldName() && pl.getName() != p.getName())
            printAt(realX - p.getX() + pl.getX(), realY - p.getY() + pl.getY(), color(char(254), pl.getColorName()));


}

std::string Game::movePlayerTo(int dirX, int dirY, std::vector<Square> content, Player* p, World* w)
{
    bool isTping(false);
    std::string dialogPath("");
    for (auto& el : content) {
        if (el.getX() == p->getX() + 2*dirX && el.getY() == p->getY() + dirY && el.getType())
            if (el.getType() == SquareType::TELEPORTER)
                if (getWorldFromPath(el.getTpPath()) != nullptr)
                {
                    getWorldFromPath(el.getTpPath())->addPlayer(p);
                    p->setX(el.getCoord().first);
                    p->setY(el.getCoord().second);
                    isTping = true;
                    p->setMovementAvailable(0);
                }
        if (el.getType() == SquareType::NPC)
            if ((el.getX() == p->getX() + 2 && el.getY() == p->getY() + dirY)
                || (el.getX() == p->getX() - 2 && el.getY() == p->getY() + dirY)
                || (el.getX() == p->getX() && el.getY() == p->getY() + 1)
                || (el.getX() == p->getX() && el.getY() == p->getY() - 1))
                dialogPath = el.getDialogPath();
    }

    if (!isTping)
    {
        p->setX(p->getX() + 2*dirX);
        p->setY(p->getY() + dirY);
        p->setMovementAvailable(p->getMovementAvailable() - 1);
        AnimatedElement ae;
        ae.init(std::string(p->getWorldName()));
        displayMap(*p, content, ae);
    }
    return dialogPath;
}

void Game::startDialog(std::string dialogPath) {
    std::ifstream f;
    std::string content;
    f.open("ressources/dialogs/" + dialogPath + ".txt");

    Dialog dlg;
    //getElements().push_back(dlg);
    while (std::getline(f, content)) {
        if (content[0] != '\0') {
            std::vector<std::string> splited = strSplit(content, "###");
            dlg.addMessage(Message(Person(splited[0], getColor(std::stoi(splited[1]))), splited[2]));
        }
    }

    f.close();
    dlg.displayConversation();
}
