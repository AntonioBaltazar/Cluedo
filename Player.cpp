#include <iostream>
#include <vector>
#include <conio.h>

#include "Utils.h"
#include "render/Square.h"
#include "World.h"
#include "Player.h"
#include "Script/Script.h"

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
std::string Player::getNotes() const { return m_notes; }
std::vector<Card> Player::getPlayerPackage() const { return m_playerPackage;}
bool Player::getCanPlay()const {return m_canPlay;};
int Player::getCanMakeHypothesis()const {return m_canMakeHypothesis;};


// Setters
void Player::setX(int x) { m_x = x; }
void Player::setY(int y) { m_y = y; }
void Player::setWorldName(std::string worldName) { m_worldName = worldName; }
void Player::setMovementAvailable(int movement) { m_mvtAvailable = movement; }
void Player::setNotes(std::string notes) { m_notes = notes; }
void Player::setPlayerPackage(Card newCard) {m_playerPackage.push_back(newCard);}
void Player::setCanPlay(bool status) {m_canPlay = status;};
void Player::setCanMakeHypothesis(int status) {m_canMakeHypothesis = status;};

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

void Player::create_player_package(std::vector<Card> &gamePackage)
{
    Card person;
    Card planet;
    Card weapon;
    Card temp;

    person = temp.card_pick(gamePackage,"Person");
    planet = temp.card_pick(gamePackage,"Planet");
    weapon = temp.card_pick(gamePackage,"Weapon");

    setPlayerPackage(person);
    setPlayerPackage(planet);
    setPlayerPackage(weapon);
}


void Player::setHypothesis(std::vector<Card> allCards)  {   m_hypothesis.make_hypothesis(allCards,false);   }

Script Player::getHypothesis()const {  return m_hypothesis;}

///Player p show a card to his opponent
void Player::show_card()
{
    Dialog d;
    int choice = menu_show_card();
    std::string sentence;

    system("CLS");

    sentence = getName()+" a la carte : "+getPlayerPackage()[choice-1].getName();

    d.displayBordersPers(50-(sentence.size()/2),70+(sentence.size()/2),12,16);
    gotoxy(60-(sentence.size()/2),14);
    std::cout<<color(sentence,getColorName());

    while(kbhit()) {}
    getch();
}


///The player can decide which card he wants to show to the opponent
int Player::menu_show_card()
{
    int choice = 0;
    int cursor = 33;
    int key = 0;
    Dialog d;

    d.displayBordersPers(20,100,9,15);

    gotoxy(42,10);
    std::cout<<color("Quelle carte souhaitez vous montrer ?",Color::Bright_White);

    ///Affichage des types de cartes
    gotoxy(35,12);
    std::cout<<color("1. Personne",Color::Yellow);
    gotoxy(55,12);
    std::cout<<color("2. Planete",Color::Blue);
    gotoxy(75,12);
    std::cout<<color("3. Arme",Color::Magenta);

    gotoxy(cursor,12);
    std::cout<<char(16);

    while(key!=13)
    {
        key = getch();
        if(key==75 && choice > 0)
            choice--;
        if(key==77 && choice < 2)
            choice++;

        gotoxy(cursor,12);
        std::cout<<" ";

        switch(choice)
        {
        case 0 : cursor = 33;  break;
        case 1 : cursor = 53;  break;
        case 2 : cursor = 73;  break;
        default : break;
        }

        gotoxy(cursor,12);
        std::cout<<char(16);
    }

    return choice+1;
}
