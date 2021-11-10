#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>

#include "World.h"
#include "render/Dice.h"
#include "Player.h"
#include "Game.h"

#include "AnimatedElement.h"
#include "Utils.h"

// Constructors & Destructor
Game::Game() {}
Game::Game(int nbOfPlayers) : m_nbOfPlayers(nbOfPlayers) {}
Game::~Game() {}

// Getters
int Game::getNbOfPlayers() const { return m_nbOfPlayers; }
std::vector<Player>& Game::getPlayers() { return m_players; }
std::vector<World>& Game::getWorlds() { return m_worlds; }
std::vector<AnimatedElement*>& Game::getElements() { return m_elements; }
World* Game::getWorldFromPath(std::string path)
{
    for (auto& world : getWorlds())
        if (world.getPath() == path)
            return &world;
    return nullptr;
}
bool Game::isFinish() const { return m_finish; }

// Setters
void Game::setNbOfPlayers(int nbOfPlayers) { m_nbOfPlayers = nbOfPlayers; }
void Game::setFinish(bool finish) { m_finish = finish; }

// Methods
void Game::addWorld(World w) { getWorlds().push_back(w); }
void Game::start()
{
    // Getting datas before launching new game
    /*askNbOfPlayers();
    askAccountOfPlayers();

    system("cls");
    */
    system("cls");
    getPlayers().push_back(Player("Martin", Color::Bright_Green, 14, 11, ""));
    getPlayers().push_back(Player("Emma", Color::Bright_Yellow, 16,12, ""));

    World board(16, 11, "Board", "maps/main");
    World realMars(18, 9, "Mars2", "maps/planets/mars");
    World realJupiter(18, 9, "jupiter2", "maps/planets/jupiter");

    for (auto& p : getPlayers())
        board.addPlayer(&p);

    addWorld(board);
    addWorld(realMars);
    addWorld(realJupiter);


    // Beginning
    Dice d;
    getElements().push_back(&d);
    int nbTurn = 0;
    while(!isFinish())
    {
        handlePlayerTurn(&getPlayers()[nbTurn % getPlayers().size()], &d);
        nbTurn++;
    }


    while(!kbhit());
    //displayMap();
}

void Game::handlePlayerTurn(Player* p, Dice* d)
{
    AnimatedElement ae;
    std::vector<Square> pWorld;
    ae.saveAsWorld(pWorld, std::string(p->getWorldName()));

    displayMap(*p, pWorld);
    p->setMovementAvailable(d->throwing());
    //p->setMovementAvailable(1000);
    int saisie;
    do {
        displayMap(*p, pWorld);

        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        saisie = getInput();
        if (saisie == 72 && p->canMoveTo(0, -1, pWorld)) movePlayerTo(0, -1, pWorld, p, getWorldFromPath(p->getWorldName()));
        if (saisie == 80 && p->canMoveTo(0, 1, pWorld)) movePlayerTo(0, 1, pWorld, p, getWorldFromPath(p->getWorldName()));
        if (saisie == 75 && p->canMoveTo(-1, 0, pWorld)) movePlayerTo(-1, 0, pWorld, p, getWorldFromPath(p->getWorldName()));
        if (saisie == 77 && p->canMoveTo(1, 0, pWorld)) movePlayerTo(1, 0, pWorld, p, getWorldFromPath(p->getWorldName()));
    } while (p->getMovementAvailable() > 0);
}

void Game::displayMap(Player p, std::vector<Square> pWorld)
{
    int realX = 60;
    int realY = 13;

    for (int i = 40; i < 100; i++)
        for (int j = 0; j < 25; j++)
            printAt(i, j, ' ');

    for (const auto& el : pWorld)
        if ((realX - p.getX() + el.getX())%120 >= 0 && (realY - p.getY() + el.getY())%25 >= 0)
        {
            int x(realX - p.getX() + el.getX()), y(realY - p.getY() + el.getY());
            bool deleting = true;
            for (auto& anel : getElements())
            {
                if (anel->getTranslatedX() <= x && x <= anel->getTranslatedX() + anel->getMaxX() &&
                     anel->getTranslatedY() <= y && y <= anel->getTranslatedY() + anel->getMaxY())
                     {
                        deleting = false;
                        break;
                     }
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

void Game::clearGlobal()
{
    int winX(120), winY(25);
    for (int i = 0; i < winX; i++)
        for (int j = 0; j < winY; j++)
        {
            bool deleting = true;
            for (auto& el : getElements())
            {
                //std::cout << "DEBUGGING";
               // std::cout << el->getMaxX() << ":" << el->getMaxY();
                //while(1);
                if (el->getTranslatedX() <= i && i <= el->getTranslatedX() + el->getMaxX() &&
                     el->getTranslatedY() <= j && j <= el->getTranslatedY() + el->getMaxY())
                    deleting = false;

            }
            if (deleting) printAt(i, j, ' ');
            //    while(1);
        }
}

void Game::movePlayerTo(int dirX, int dirY, std::vector<Square> content, Player* p, World* w)
{
    for (auto& el : content)
        if (el.getX() == p->getX() + 2*dirX && el.getY() == p->getY() + dirY && el.getType())
            if (el.getType() == SquareType::TELEPORTER)
            {
                if (getWorldFromPath(el.getTpPath()) != nullptr)
                {
                    getWorldFromPath(el.getTpPath())->addPlayer(p);
                    p->setX(el.getCoord().first);
                    p->setY(el.getCoord().second);
                    p->setMovementAvailable(0);
                }
            }

    p->setX(p->getX() + 2*dirX);
    p->setY(p->getY() + dirY);
    p->setMovementAvailable(p->getMovementAvailable() - 1);
}

void Game::askAccountOfPlayers()
{
    system("cls");
    std::string adjectives[] = {"Premier", "Second", "Troisi", "Quatri", "Cinqui", "Sixi"};

    AnimatedElement sharp(16, 11);
    AnimatedElement nb(32, 11);
    sharp.render("numbers/sharp");

    int saisie, index;

    for (int i = 0; i < getNbOfPlayers(); i++)
    {
    std::string pseudo;
    index = 0;
    // Clearing old text
    nb.clearArea(14, 7);
    for (int i = 0; i < 28; i++)
        for (int j = 0; j < 3; j++)
            printAt(48+i, 12+j, " ");

    nb.render("numbers/" + std::to_string(i+1));
    gotoxy(48, 12);
    std::cout << color(adjectives[i], Color::Bright_Yellow);
    if (i > 1) std::cout << color(char(138), Color::Bright_Yellow) << color("me", Color::Bright_Yellow);
    std::cout << color(" joueur,", Color::Bright_White);
    printAt(48, 13, color("saississez votre nom :", Color::Bright_White));

    do
    {
        saisie = getInput();
        if (((saisie >= 'a' && saisie <= 'z') || (saisie >= 'A' && saisie <= 'Z') || saisie == ' ') && index < 19)
        {
            pseudo += (char)saisie;
            printAt(48 + index, 14, std::string(1, char(saisie)));
            index++;
        } else if (saisie == 8 && index > 0)
        {
             pseudo.pop_back();
             index--;
             printAt(48 + index, 14, " ");
        }
    } while (saisie != 13 || saisie < 2);
    getPlayers().push_back(Player(pseudo, Color::Bright_Cyan));
}
}

void Game::askNbOfPlayers()
{
    system("cls");
    int nbOfPlayers = 2;
    int saisie = -1;
    gotoxy(40, 12);
    std::cout << char(16);
    std::cout << color(" Nombre de joueurs ?", Color::Bright_White);
    gotoxy(42,13);
    std::cout << "De 2 " << char(133) <<" 6";
    AnimatedElement nb(65, 11);

    do
    {
        nb.clearArea(14, 7);
        nb.render("numbers/" + std::to_string(nbOfPlayers));
        gotoxy(42, 15);
        for (int i = 0; i < 12; i++) std::cout << " ";
        gotoxy(42, 15);
        for (int i = 0; i < nbOfPlayers; i++) std::cout << color(char(3), Color::Red) << " ";
        while (!kbhit());
        saisie = getch();
        if (saisie == 72 && nbOfPlayers < 6) nbOfPlayers++;
        if (saisie == 80 && nbOfPlayers > 2) nbOfPlayers--;
    } while (saisie != 13);
    setNbOfPlayers(nbOfPlayers);
}
