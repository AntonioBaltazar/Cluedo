#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

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
};


#endif // PLAYER_H_INCLUDED
