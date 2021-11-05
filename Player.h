#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "Dialog.h"
#include "render/Square.h"
#include "World.h"

class Player : public Person {
private:
    int m_x;
    int m_y;
    std::string m_worldName;
public:
    // Constructors & Destructor
    Player();
    Player(std::string, Color color);
    Player(std::string name, Color color, int x, int y, std::string worldName);
    ~Player();

    // Getters
    int getX() const;
    int getY() const;
    std::string getWorldName() const;

    // Setters
    void setX(int x);
    void setY(int y);
    void setWorldName(std::string worldName);

    // Methods
    bool canMoveTo(int dirX, int dirY, std::vector<Square> world);
    //void moveTo(int dirX, int dirY, std::vector<Square> content, World* w);
    void npcAround(std::vector<Square> world);
    void actionMenu();
    void teleport(Square sq);
};

#endif // PLAYER_H_INCLUDED
