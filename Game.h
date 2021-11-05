#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "World.h"
#include "Player.h"

class Game {
private:
    int m_nbOfPlayers;
    std::vector<Player> m_players;
    std::vector<World> m_worlds;
public:
    // Constructors & Destructor
    Game();
    Game(int nbOfPlayer);
    ~Game();

    // Getters
    int getNbOfPlayers() const;
    std::vector<Player>& getPlayers();
    std::vector<World>& getWorlds();
    World* getWorldFromName(std::string name);

    // Setters
    void setNbOfPlayers(int nbOfPlayers);

    // Methods
    void addWorld(World w);
    void start();
    void askNbOfPlayers();
    void askAccountOfPlayers();
    void displayMap(Player p, std::vector<Square> pWorld);
    void handlePlayerTurn(Player p);
    void movePlayerTo(int dirX, int dirY, std::vector<Square> content, Player* p, World* w);
};

#endif // GAME_H_INCLUDED
