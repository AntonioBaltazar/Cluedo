#include <iostream>
#include <windows.h>
#include <conio.h>
#include "Game.h"
#include "AnimatedElement.h"

// Constructors & Destructor
Game::Game() {}
Game::Game(int nbOfPlayers) : m_nbOfPlayers(nbOfPlayers) {}
Game::~Game() {}

// Getters
int Game::getNbOfPlayers() const { return m_nbOfPlayers; }

// Setters
void Game::setNbOfPlayers(int nbOfPlayers) { m_nbOfPlayers = nbOfPlayers; }

// Methods
void Game::start()
{
    askNbOfPlayers();
}

void Game::askNbOfPlayers()
{
    system("cls");
    int nbOfPlayers = 2;
    int saisie = -1;
    std::cout << "Combien de joueurs ? (2 à 6)";

    do
    {
        while (!kbhit());
        saisie = getch();
        if (saisie == 72 && nbOfPlayers < 6) nbOfPlayers++;
        if (saisie == 80 && nbOfPlayers > 2) nbOfPlayers--;
        AnimatedElement nb(50, 12);
        nb.clearArea(14, 7);
        nb.render("numbers/" + std::to_string(nbOfPlayers));
        //std::cout << nbOfPlayers << "\n";
    } while (saisie != 13);
}
