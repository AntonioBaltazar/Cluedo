#include <iostream>
#include <vector>
#include <algorithm>

#include "World.h"
#include "Player.h"

// Constructors & Destructor
World::World() {}
World::World(std::string name, std::string path) : m_name(name), m_path(path) {}
World::~World() {}

// Getters
std::string World::getName() const { return m_name; }
std::string World::getPath() const { return m_path; }
std::vector<Player*>& World::getPlayers() { return m_players;}

// Setters
void World::setName(std::string name) { m_name = name; }
void World::setPath(std::string path) { m_path = path; }

// Methods
void World::addPlayer(Player* p)
{
    getPlayers().push_back(p);
    p->setWorldName(getPath());
}
bool World::containsPlayer(Player p)
{
    for (const auto& pl : getPlayers())
        if (pl->getName() == p.getName())
            return true;
    return false;
}
