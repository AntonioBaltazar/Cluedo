#include <iostream>
#include <vector>
#include <algorithm>

#include "World.h"
#include "render/Blackhole.h"

// Constructors & Destructor
World::World() {}
World::World(int x, int y, std::string name, std::string path) : m_originX(x), m_originY(y), m_name(name), m_path(path) {}
World::~World() {}

// Getters
int World::getOriginX() const { return m_originX; }
int World::getOriginY() const { return m_originY; }
std::string World::getName() const { return m_name; }
std::string World::getPath() const { return m_path; }
std::vector<Player*>& World::getPlayers() { return m_players;}

// Setters
void World::setOriginX(int x) { m_originX = x; }
void World::setOriginY(int y) { m_originY = y; }
void World::setName(std::string name) { m_name = name; }
void World::setPath(std::string path) { m_path = path; }

// Methods
void World::addPlayer(Player* p)
{
    getPlayers().push_back(p);
    p->setX(getOriginX());
    p->setY(getOriginY());
    p->setWorldName(getPath());
}
bool World::containsPlayer(Player p)
{
    for (const auto& pl : getPlayers())
        if (pl->getName() == p.getName())
            return true;
    return false;
}
