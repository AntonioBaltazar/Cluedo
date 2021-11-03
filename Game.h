#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <vector>
#include "Dialog.h"
#include "Player.h"

class Game {
private:
    int m_nbOfPlayers;
    std::vector<Person> m_players;
public:
    // Constructors & Destructor
    Game();
    Game(int nbOfPlayer);
    ~Game();

    // Getters
    int getNbOfPlayers() const;
    std::vector<Person>& getPlayers();

    // Setters
    void setNbOfPlayers(int nbOfPlayers);

    // Methods
    void start();
    void askNbOfPlayers();
    void askAccountOfPlayers();
    void displayMap(Player p);
};

#endif // GAME_H_INCLUDED
