#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED

#include <vector>
#include "Player.h"
#include "World.h"

class World {
private:
    int m_originX;
    int m_originY;
    std::string m_name;
    std::string m_path;
    std::vector<Player*> m_players;
public:
    // Constructors & Destructor
    World();
    World(int x, int y, std::string name, std::string path);
    ~World();

    // Getters
    int getOriginX() const;
    int getOriginY() const;
    std::string getName() const;
    std::string getPath() const;
    std::vector<Player*>& getPlayers();

    // Setters
    void setOriginX(int x);
    void setOriginY(int y);
    void setName(std::string name);
    void setPath(std::string path);

    // Methods
    void addPlayer(Player* p);
    bool containsPlayer(Player p);
};


#endif // WORLD_H_INCLUDED
