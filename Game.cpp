#include <iostream>
#include <windows.h>
#include <algorithm>
#include <conio.h>
#include <vector>
#include <string>
#include <fstream>
#include <typeinfo>
#include <time.h>
#include "World.h"
#include "render/Dice.h"
#include "Player.h"
#include "Game.h"
#include "AnimatedElement.h"
#include "Utils.h"
#include "Dashboard/Dashboard.h"
#include "render/Blackhole.h"

// Methods
void Game::addWorld(World w) { getWorlds().push_back(w); }

void Game::start()
{
    // Getting datas before launching new game
    getPlayers().push_back(Player("Martin", Color::Bright_Green, 14, 11, ""));
    getPlayers().push_back(Player("Emma", Color::Bright_Yellow, 16,12, ""));
    //Card package creation and shuffle
    setAllPackages();

    //Card distribution to all the players
    cardDistrib();

    //We create a new script for the game
    setSolution();

    system("cls");

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
    Dashboard db(94, 3, 25, 17);
    getDashboard() = db;
    Notepad np(2, 25, 25, 3);
    getNotepad() = np;
    np.renderTurn();

    getElements().push_back(&d);
    getElements().push_back(&db);
    getElements().push_back(&np);

    int nbTurn = 0, eliminated = 0;
    while(!isFinish())
    {
        if(getPlayers()[nbTurn % getPlayers().size()].getCanPlay())
            handlePlayerTurn(&getPlayers()[nbTurn % getPlayers().size()], &d, getPlayers()[(nbTurn+1) % getPlayers().size()]);
        else
            eliminated++;
        if(eliminated == getPlayers().size())
            gameOver();
        nbTurn++;
    }

    while(!kbhit());
}

void Game::gameOver()
{
    Dialog d;
    AnimatedElement anel;
    Player p;

    d.addMessage(Message(p,"GAME OVER"));
    showStars(anel,p);
    d.displayBordersPers(48,70,11,15);
    d.displayMessResultHyp(45,10,false);


    setFinish(true);
}

void Game::handlePlayerTurn(Player* p, Dice* d, Player nextPlayer)
{
    for (auto& w : getWorlds())
        if (w.getPath() == p->getWorldName())
            getDashboard().renderTurn(p, w.getName());
    AnimatedElement ae;
    std::vector<Square> pWorld;
    ae.saveAsWorld(pWorld, std::string(p->getWorldName()));
    ae.init(std::string(p->getWorldName()));

    displayMap(*p, pWorld, ae);
    if (p->getWorldName() == "maps/main")
        p->setMovementAvailable(d->throwing());
    else
        p->setMovementAvailable(-1);

    for (auto& w : getWorlds())
        if (w.getPath() == p->getWorldName())
            getDashboard().renderTurn(p, w.getName());

    int saisie;
    do
    {
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        saisie = getInput();

        if (saisie == 72 && p->canMoveTo(0, -1, pWorld)) movePlayerTo(0, -1, pWorld, p, getWorldFromPath(p->getWorldName()));
        else if (saisie == 80 && p->canMoveTo(0, 1, pWorld)) movePlayerTo(0, 1, pWorld, p, getWorldFromPath(p->getWorldName()));
        else if (saisie == 75 && p->canMoveTo(-1, 0, pWorld)) movePlayerTo(-1, 0, pWorld, p, getWorldFromPath(p->getWorldName()));
        else if (saisie == 77 && p->canMoveTo(1, 0, pWorld)) movePlayerTo(1, 0, pWorld, p, getWorldFromPath(p->getWorldName()));
        else if (saisie == 110 || saisie == 78)
        {
            handleNotepad(p);
            displayMap(*p, pWorld, ae);
        } else if (saisie == 32)
        {
            findDialog(pWorld, p);
            displayMap(*p, pWorld, ae);
        }else if(saisie == 104) //Hypothesis
        {

            getSolution().display();
            int c = getInput();
            setFinish(handleHypothesis(p,nextPlayer));
            p->setMovementAvailable(0);
        }
    }
    while (p->getMovementAvailable() > 0 || p->getMovementAvailable() == -1);
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
                if (anel->getTranslatedX() <= x && x <= anel->getTranslatedX() + anel->getMaxX() &&
                        anel->getTranslatedY() <= y && y <= anel->getTranslatedY() + anel->getMaxY())
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

void Game::movePlayerTo(int dirX, int dirY, std::vector<Square>& content, Player* p, World* w)
{
    bool isTping(false);
    for (auto& el : content)
        if (el.getX() == p->getX() + 2*dirX && el.getY() == p->getY() + dirY && el.getType())
            if (el.getType() == SquareType::TELEPORTER)
                if (getWorldFromPath(el.getTpPath()) != nullptr)
                {
                    getWorldFromPath(el.getTpPath())->addPlayer(p, true);
                    p->setX(el.getCoord().first);
                    p->setY(el.getCoord().second);
                    isTping = true;
                    p->setMovementAvailable(0);
                    if (el.getTpPath() != "maps/main")
                    {
                        srand(time(NULL));
                        if (rand() % 3 == 0)  {
                            system("cls");
                            Blackhole bh(15, 2, "blackhole", "Trou noir");
                            bh.render(" voyage un peu trop proche d'un trou noir..", p->getName());
                            break;
                        }
                        p->setMovementAvailable(-1);
                        AnimatedElement ae;
                        content.clear();
                        ae.saveAsWorld(content, std::string(el.getTpPath()));
                        for (auto& w : getWorlds())
                                if (w.getPath() == p->getWorldName())
                                    getDashboard().renderTurn(p, w.getName());
                            getNotepad().renderTurn();
                    }
                    break;
                }
    if (!isTping)
    {
        p->setX(p->getX() + 2*dirX);
        p->setY(p->getY() + dirY);
        if (p->getMovementAvailable() != - 1)
            p->setMovementAvailable(p->getMovementAvailable() - 1);

        for (auto& w : getWorlds())
            if (w.getPath() == p->getWorldName())
                getDashboard().renderTurn(p, w.getName());
    }
    AnimatedElement ae;
    ae.init(std::string(p->getWorldName()));
    displayMap(*p, content, ae);
}

template<typename T, typename K>
inline bool isType(const K &k) {
    return typeid(T).hash_code() == typeid(k).hash_code();
}

void Game::handleNotepad(Player* p)
{
    for (auto& el : getElements())
        if (isType<Notepad>(*el)) {
            Notepad* np = dynamic_cast<Notepad*>(el);
            np->setTranslated(2, 14);
            np->setMax(25, 14);
            np->renderTurn();
            p->setNotes(np->open(p->getNotes()));
            np->setTranslated(2, 25);
            np->setMax(25, 3);
            np->renderTurn();
            break;
        }
}

void Game::findDialog(std::vector<Square> content, Player* p)
{
    std::string dialogPath("");
    for (auto& el : content) {
        if (el.getType() == SquareType::NPC)
            if ((el.getX() == p->getX() + 2 && el.getY() == p->getY())
                || (el.getX() == p->getX() - 2 && el.getY() == p->getY())
                || (el.getX() == p->getX() && el.getY() == p->getY() + 1)
                || (el.getX() == p->getX() && el.getY() == p->getY() - 1))
                dialogPath = el.getDialogPath();
    }
    if (dialogPath != "")
         startDialog(dialogPath);
}

void Game::startDialog(std::string dialogPath)
{
    std::ifstream f;
    std::string content;
    f.open("ressources/dialogs/" + dialogPath + ".txt");

    Dialog dlg(30, 22, 89, 6);
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


void Game::rules()
{
    system("cls");
    //Animation: stars in the background
    Player p;
    AnimatedElement world;
    showStars(world,p);

    std::string title = "R\xd4GLES";
    std::string under = "-=-=-=-=-=-=-=-=-=-=-=-";
    printAt(60 - under.size()/2, 2, color(under, Color::Bright_Yellow));
    printAt(60 - title.size()/2, 3, color(title, Color::Bright_White));
    printAt(60 - under.size()/2, 4, color(under, Color::Bright_Yellow));

    /*
    1. Retour au menu
    2. Affichage du texte
    3. Encadrement du texte
    */

    std::string sentence = "La partie commence dans le hall. Le premier joueur lance le d\x82 et avance dans le couloir d\'autant de cases que son score le lui permet. Objectif : entrer dans une des plan\x8ates pour pouvoir enqu\x88ter. Par exemple si vous vous trouvez sur Mars vous pouvez \x82mettre cette hypoth\x8ase : \"Je pense que c\'est Martin avec la matraque, sur Mars\". Si un des autres joueurs poss\x8ade une des cartes de votre hypoth\x8Ase il doit vous la montrer discr\x8atement. Ainsi vous pouvez rayer une arme, un lieu ou un suspect et vous rapprocher de la solution de l\'\x82nigme.\n Au prochain tour, vous pourrez ressortir par la porte de votre choix et ainsi se diriger vers la prochaine salle.\n Attention aux trous noirs qui vous font sauter des tours...\n Lorsqu\'un joueur pense avoir trouv\x82 la r\x82ponse de l\'\x82nigme, il doit formuler son accusation. Il note discr\x8atement sur un papier le lieu du meurtre, l\'arme du crime et l\'assassin, puis v\x82rifie dans l\'\x82tui \x85 \x82nigme son accusation. Attention, vous ne pouvez faire qu\'une seule accusation par partie !!\n Si le joueur a raison, il annonce les trois cartes de l\'\x82nigme aux autres joueurs. Ainsi, la partie se termine et le joueur est proclam\x82 vainqueur.\n Si le joueur a tort, il doit remettre les 3 cartes dans l\'\x82tui \x85 \x82nigme, sans rien dire, et la partie continue pour les autres joueurs. Le joueur qui s\'est tromp\x82 est hors du jeu cependant il doit toujours montrer ses cartes pour contredire l\'hypoth\x88se dun autre joueur.\n Ne vous faites pas avoir..";
    std::vector<std::string> sentences = strSplit(sentence, " ");
    int x1(20), x2(85);
    int y(6);

    //On veut afficher une phrase, si trop longue = retour à la ligne
    int indexX(0), indexY(0);
    for (auto& str : sentences)
    {
        if (str.find("\\n") != std::string::npos)
        {
            eraseAllSubStr(str, "\\n");
            indexX = 0;
            indexY++;
        }

        if (indexX + str.size() < x2)
        {
            printAt(x1 + indexX, y + indexY, str + " ");
            indexX += str.size() + 1;
        } else
        {
            indexX = 0;
            indexY++;
            printAt(x1 + indexX, y + indexY, str + " ");        }
    }

    //Animation of text to flash
    std::string text = "Pour retourner au menu, appuyez sur une touche";

    while (!kbhit())
    {
        gotoxy(60 - text.size()/2, 24);
        std::cout << "\033[97m";
        std::cout << text;
        std::cout << "\033[37m";
        if (kbhit()) break;
        Sleep(600);

        gotoxy(60 - text.size()/2, 24);
        std::cout << std::string(text.size(), ' ');
        if (kbhit()) break;
        Sleep(600);
    }
    getch();
}
