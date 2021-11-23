#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "World.h"
#include "Player.h"
#include "AnimatedElement.h"

class Game {
private:
    int m_nbOfPlayers;
    std::vector<Player> m_players;
    std::vector<World> m_worlds;
    std::vector<AnimatedElement> m_elements;
    std::vector<Card> m_gamePackage;
    int m_nbCard;
    bool m_finish = false;
public:
    // Constructors & Destructor
    Game();
    Game(int nbOfPlayer);
    ~Game();

    // Getters
    int getNbOfPlayers() const;
    std::vector<Player>& getPlayers();
    std::vector<World>& getWorlds();
    std::vector<AnimatedElement>& getElements();
    World* getWorldFromPath(std::string path);
    bool isFinish() const;

    // Setters
    void setNbOfPlayers(int nbOfPlayers);
    void setFinish(bool finish);

    void setNbCard(int nbCard);

    void setGamePackage();
    std::vector<Card> getGamePackage();
    std::vector<Card> createGamePackage();
    void displayPackage(std::vector<Card> Gamepackage);

    // Methods
    void addWorld(World w);
    void start();
    void askNbOfPlayers();
    void askAccountOfPlayers();
    void displayMap(Player p, std::vector<Square> pWorld);
    void handlePlayerTurn(Player* p);
    std::string movePlayerTo(int dirX, int dirY, std::vector<Square> content, Player* p, World* w);
    void clearGlobal();
    void startDialog(std::string dialogPath);

};

#endif // GAME_H_INCLUDED
