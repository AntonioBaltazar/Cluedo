#include <iostream>
#include "Dialog.h"
#include "Player.h"
#include "render/Square.h"

// Constructors & Destructor
Player::Player() : Person() {}
Player::Player(std::string name, Color color, int x, int y, std::string worldName)
    : Person(name, color), m_x(x), m_y(y), m_worldName(worldName) {}
Player::~Player() {}

// Getters
int Player::getX() const { return m_x; }
int Player::getY() const { return m_y; }
std::string Player::getWorldName() const { return m_worldName; }

// Setters
void Player::setX(int x) { m_x = x; }
void Player::setY(int y) { m_y = y; }
void Player::setWorldName(std::string worldName) { m_worldName = worldName; }

// Methods
bool Player::canMoveTo(int dirX, int dirY, std::vector<Square> world)
{
    for (const auto& el : world)
        if (el.getX() == getX() + 2*dirX && el.getY() == getY() + dirY && el.getType() != SquareType::TELEPORTER)
            return false;
    return true;
}

void Player::npcAround(std::vector<Square> world)
{
    // Searching npcs
    std::vector<Square> npcs;
    for (const auto& el : world)
        if (el.getType() == SquareType::NPC)
            npcs.push_back(el);

    //for (const auto& el : npcs)
      //  if ()
}
