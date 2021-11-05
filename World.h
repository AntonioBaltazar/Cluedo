#ifndef WORLD_H_INCLUDED
#define WORLD_H_INCLUDED
#include "Player.h"

class World {
private:
    std::string m_name;
    std::string m_path;
    std::vector<Player*> m_players;
public:
    // Constructors & Destructor
    World();
    World(std::string name, std::string path);
    ~World();

    // Getters
    std::string getName() const;
    std::string getPath() const;
    std::vector<Player*>& getPlayers();

    // Setters
    void setName(std::string name);
    void setPath(std::string path);

    // Methods
    void addPlayer(Player* p);
    bool containsPlayer(Player p);
};


#endif // WORLD_H_INCLUDED
