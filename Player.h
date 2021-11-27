#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED


#include "Dialog.h"
#include "render/Square.h"
#include "Card/Card.h"
#include "Script/Script.h"

class Player : public Person {
private:
    int m_x;
    int m_y;
    std::string m_worldName;
    int m_mvtAvailable = 0;
    std::string m_notes;
    std::vector<Card> m_playerPackage; //[0] : person | [1] : planet | [2] : weapon
    Script m_hypothesis;
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
    int getMovementAvailable() const;
    std::string getNotes() const;
    std::vector<Card> getPlayerPackage()const;
    Script getHypothesis()const;

    // Setters
    void setX(int x);
    void setY(int y);
    void setWorldName(std::string worldName);
    void setMovementAvailable(int movement);
    void setNotes(std::string notes);
    void setPlayerPackage(Card newCard);
    void setHypothesis(std::vector<Card> allCards);

    // Methods
    bool canMoveTo(int dirX, int dirY, std::vector<Square> world);
    //void moveTo(int dirX, int dirY, std::vector<Square> content, World* w);
    void npcAround(std::vector<Square> world);
    void actionMenu();
    void teleport(Square sq);
    void create_player_package(std::vector<Card> &gamePackage);
    void show_card();
    int menu_show_card();
};
#endif // PLAYER_H_INCLUDED
