#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "render/Square.h"

class Player : public Person {
private:
    int m_x;
    int m_y;
    std::string m_worldName;
public:
    // Constructors & Destructor
    Player();
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
    bool canMoveTo(int dirX, int dirY, std::vector<Square>);
};


#endif // PLAYER_H_INCLUDED
