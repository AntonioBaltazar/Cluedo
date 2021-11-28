#include <iostream>
#include <windows.h>
#include <algorithm>
#include <conio.h>
#include <vector>
#include <fstream>

#include "../World.h"
#include "../render/Dice.h"
#include "../Player.h"
#include "../Game.h"
#include "../AnimatedElement.h"
#include "../Utils.h"

// Constructors & Destructor
Game::Game() {}
Game::Game(int nbOfPlayers) : m_nbOfPlayers(nbOfPlayers) {}
Game::~Game() {}

// Getters
int Game::getNbOfPlayers() const { return m_nbOfPlayers; }
std::vector<AnimatedElement*>& Game::getElements() { return m_elements; }
std::vector<Player>& Game::getPlayers() { return m_players; }
std::vector<World>& Game::getWorlds() { return m_worlds; }
Dashboard& Game::getDashboard() { return m_dashboard; }
Notepad& Game::getNotepad() { return m_notepad; }
Dice& Game::getDice() { return m_dice; }
int Game::getTurn() const { return m_turn; }
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
void Game::newTurn() { m_turn++; }
