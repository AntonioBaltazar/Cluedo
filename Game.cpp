#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Game.h"
#include "AnimatedElement.h"
#include "Utils.h"
#include "Player.h"

// Constructors & Destructor
Game::Game() {}
Game::Game(int nbOfPlayers) : m_nbOfPlayers(nbOfPlayers) {}
Game::~Game() {}

// Getters
int Game::getNbOfPlayers() const { return m_nbOfPlayers; }
std::vector<Person>& Game::getPlayers() { return m_players; }

// Setters
void Game::setNbOfPlayers(int nbOfPlayers) { m_nbOfPlayers = nbOfPlayers; }

// Methods
void Game::start()
{
    // Getting datas before launching new game
    /*askNbOfPlayers();
    askAccountOfPlayers();

    system("cls");
    std::cout << "Pseudos:\n";
    for (size_t i = 0; i < getPlayers().size(); i++)
        std::cout << getPlayers()[i].getName() << "\n";
    while (!kbhit());*/

    system("cls");
    Player p("Martin", Color::Bright_Green, 14, 11, "maps/main");
    displayMap(p);

    while(!kbhit());
    //displayMap();
}
void Game::displayMap(Player p)
{
    AnimatedElement ae;
    std::vector<Square> pWorld;
    ae.saveAsMap(pWorld, std::string(p.getWorldName()));

    int realX = 60;
    int realY = 13;
    int saisie;

    // Print player

    do {
        system("cls");
        for (const auto& el : pWorld)
            printAt((realX - p.getX() + el.getX())%120 , (realY - p.getY() + el.getY())%25, color(el.getContent(), el.getColor()));
        printAt(realX, realY, "X");
        saisie = getInput();
        if (saisie == 72 && p.canMoveTo(0, -1, pWorld)) p.setY(p.getY()-1);
        if (saisie == 80 && p.canMoveTo(0, 1, pWorld)) p.setY(p.getY()+1);
        if (saisie == 75 && p.canMoveTo(-1, 0, pWorld)) p.setX(p.getX()-2);
        if (saisie == 77 && p.canMoveTo(1, 0, pWorld)) p.setX(p.getX()+2);

        p.npcAround(pWorld);

    } while (saisie != 13);

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
        getPlayers().push_back(Person(pseudo, Color::Bright_Cyan));
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
