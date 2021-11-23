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
<<<<<<< HEAD
#include "Dashboard/Dashboard.h"
=======
// Constructors & Destructor
Game::Game()
{
    //getElements().clear();
}
Game::Game(int nbOfPlayers) : m_nbOfPlayers(nbOfPlayers) {}
Game::~Game() {}
// Getters
int Game::getNbOfPlayers() const { return m_nbOfPlayers; }
std::vector<AnimatedElement>& Game::getElements() { return m_elements; }
std::vector<Player>& Game::getPlayers() { return m_players; }
std::vector<World>& Game::getWorlds() { return m_worlds; }
World* Game::getWorldFromPath(std::string path)
{
    for (auto& world : getWorlds())
        if (world.getPath() == path)
            return &world;
    return nullptr;
}
bool Game::isFinish() const
{
    return m_finish;
}
// Setters
void Game::setNbOfPlayers(int nbOfPlayers) { m_nbOfPlayers = nbOfPlayers; }
void Game::setFinish(bool finish) {  m_finish = finish;  }
>>>>>>> 6ff70f6d688c2a57c326c560125c12ff3bba915c

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
    //Card package creation and shuffle
    //setGamePackage();
    //displayPackage(getGamePackage()); //AFFICHAGE DU PAQUET DE CARTE INITIALE

    // Getting datas before launching new game
    /*askNbOfPlayers();
    askAccountOfPlayers();
    */
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

    ///Le mélanger

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

<<<<<<< HEAD
=======
void Game::clearGlobal()
{
    int winX = 120, winY = 30;
        std::vector<std::pair<int, int>> elementSlices;
    for (int i = 0; i < winY; i++)
    {
        // Getting element's slices
        elementSlices.clear();
        for (const auto& element : getElements())
            if (i >= element.getTranslatedY() && i <= element.getTranslatedY() + element.getMaxY() + 1)
                elementSlices.push_back(std::pair<int, int>(element.getTranslatedX(), element.getMaxX() + 1));

        int stringX = 0;
        // Printing slices of spaces char
        for (const auto& slice : elementSlices)
        {
            printAt(stringX, i, std::string(slice.first, ' '));
            stringX += slice.first + slice.second;

        }

        printAt(stringX, i, std::string(winX - (stringX > 120 ? 0 : stringX), ' '));
    }
}

>>>>>>> 6ff70f6d688c2a57c326c560125c12ff3bba915c
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
        for (int j = 0; j < 3; j++)
            printAt(48, j+i, std::string(28, ' '));

        nb.render("numbers/" + std::to_string(i+1));
        gotoxy(48, 12);
        std::cout << color(adjectives[i], Color::Bright_Yellow);
        if (i > 1) std::cout << color(char(138), Color::Bright_Yellow) << color("me", Color::Bright_Yellow);
        std::cout << color(" joueur,", Color::Bright_White);
        printAt(48, 13, color("saississez votre nom :", Color::Bright_White));

        do
        {
            saisie = getInput();
            gotoxy(48, 12);

            if (((saisie >= 'a' && saisie <= 'z') || (saisie >= 'A' && saisie <= 'Z') || saisie == ' ') && index < 19)
            {
                pseudo += (char)saisie;
                printAt(48 + index, 14, std::string(1, char(saisie)));
                index++;
            }
            else if (saisie == 8 && index > 0)
            {
                pseudo.pop_back();
                index--;
                printAt(48 + index, 14, " ");
            }
        }
        while (saisie != 13 || saisie < 2);
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
        saisie = getInput();
        if (saisie == 72 && nbOfPlayers < 6) nbOfPlayers++;
        if (saisie == 80 && nbOfPlayers > 2) nbOfPlayers--;
    } while (saisie != 13);
    setNbOfPlayers(nbOfPlayers);
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
