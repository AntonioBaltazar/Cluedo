#include <iostream>
#include <vector>

#include "Utils.h"
#include "render/Square.h"

#include "World.h"
#include "Player.h"

// Constructors & Destructor
Player::Player() : Person() {}
Player::Player(std::string name, Color color, int x, int y, std::string worldName)
    : Person(name, color), m_x(x), m_y(y), m_worldName(worldName) {}
Player::Player(std::string name, Color color) : Person(name, color) {}
Player::~Player() {}

// Getters
int Player::getX() const { return m_x; }
int Player::getY() const { return m_y; }
std::string Player::getWorldName() const { return m_worldName; }
int Player::getMovementAvailable() const { return m_mvtAvailable; }
std::vector<Card> Player::getPlayerPackage() const { return m_playerPackage;}


// Setters
void Player::setX(int x) { m_x = x; }
void Player::setY(int y) { m_y = y; }
void Player::setWorldName(std::string worldName) { m_worldName = worldName; }
void Player::setMovementAvailable(int movement) { m_mvtAvailable = movement; }
void Player::setPlayerPackage(Card newCard) {m_playerPackage.push_back(newCard);}

// Methods
bool Player::canMoveTo(int dirX, int dirY, std::vector<Square> world)
{
    for (const auto& el : world)
        if (el.getX() == getX() + 2*dirX && el.getY() == getY() + dirY && el.getType() != SquareType::TELEPORTER)
            return false;
    return true;
}

void Player::teleport(Square sq)
{
    if (sq.getType() == SquareType::TELEPORTER)
        setWorldName(sq.getTpPath());
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

void Player::actionMenu()
{
    int input, choice = 1;
    std::string sentences[] = {"1. Se deplacer", "2. Enoncer une hypothese"};
    do
    {
        if (input == 72 && choice > 1) choice--;
        if (input == 80 && choice < 2) choice++;
        for (int i = 0; i < 40; i++) printAt(65+i, 20, " ");
        printAt(80 - sentences[choice-1].size()/2, 20, sentences[choice-1]);
        input = getInput();
    } while (input != 13);

    switch(choice)
    {
        case 1 :
            break;
        case 2 :
            break;
    }
}

void Player::create_player_package(std::string type, std::string name)
{
    Card newcard;

    newcard.setName(name);
    newcard.setType(name);

    setPlayerPackage(newcard);
}

void Player::create_player_package(Card newcard) {    setPlayerPackage(newcard);    }
