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
    Dashboard m_dashboard;
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
    Dashboard& getDashboard();
    World* getWorldFromPath(std::string path);
    bool isFinish() const;

    // Setters
    void setNbOfPlayers(int nbOfPlayers);
    void setFinish(bool finish);
    void setNbCard(int nbCard);
    void setGamePackage();
    std::vector<Card> getGamePackage();


    // Methods

    //Setup
    void start();
    void addWorld(World w);
    void askNbOfPlayers();
    void askAccountOfPlayers();
    std::vector<Card> createGamePackage();
    void cardDistrib();

    //In-game
    void displayMap(Player p, std::vector<Square> pWorld, AnimatedElement world);
    void handlePlayerTurn(Player* p, Dice* d);
    std::string movePlayerTo(int dirX, int dirY, std::vector<Square> content, Player* p, World* w);
    void clearGlobal();
    void startDialog(std::string dialogPath);
    void showStars(AnimatedElement world, Player p);

    //Extra
    void displayPackage(std::vector<Card> Gamepackage);

};

#endif // GAME_H_INCLUDED
