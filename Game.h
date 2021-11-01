#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

class Game {
private:
    int m_nbOfPlayers;
public:
    // Constructors & Destructor
    Game();
    Game(int nbOfPlayer);
    ~Game();

    // Getters
    int getNbOfPlayers() const;

    // Setters
    void setNbOfPlayers(int nbOfPlayers);

    // Methods
    void start();
    void askNbOfPlayers();
    void askAccountOfPlayers();
};

#endif // GAME_H_INCLUDED
