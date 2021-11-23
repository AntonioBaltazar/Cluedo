#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include "World.h"
#include "Player.h"
#include "AnimatedElement.h"
#include "render/Dice.h"
#include "Dashboard/Dashboard.h"

class Game {
private:
    int m_nbOfPlayers;
    std::vector<Player> m_players;
    std::vector<World> m_worlds;
    std::vector<AnimatedElement> m_elements;
<<<<<<< HEAD
    Dashboard m_dashboard;
=======
    std::vector<Card> m_gamePackage;
    int m_nbCard;
>>>>>>> 6ff70f6d688c2a57c326c560125c12ff3bba915c
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
    Dashboard& getDashboard();
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
    void displayMap(Player p, std::vector<Square> pWorld, AnimatedElement world);
    void handlePlayerTurn(Player* p, Dice* d);
    std::string movePlayerTo(int dirX, int dirY, std::vector<Square> content, Player* p, World* w);
    void clearGlobal();
    void startDialog(std::string dialogPath);

    void showStars(AnimatedElement world, Player p);

};

#endif // GAME_H_INCLUDED
