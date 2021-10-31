#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include <vector>
#include <string>

#define WEAPON 5
#define ROOM 5
#define SUSPECTS 5
#define NBCARDS 19

class Card
{
private:
    std::string m_type;
    std::string m_name;

public:

    ///Constructor and Destructor
    Card();
    Card(std::string type, std::string name);
    ~Card();

    ///Getter
    std::string getType()const;
    std::string getName()const;

    ///Setter
    void setType(std::string type);
    void setName(std::string name);

    ///Methods
    void display();
};

///Prototype
std::vector<Card> card_Creation();
Card card_convert(std::string content);
std::vector<Card> card_Shuffle(std::vector<Card> myPackage);
void card_Package_Display(std::vector<Card> myPackage);
void card_Management();

Card card_pick(std::vector<Card> &myPackage);




#endif // CARD_H_INCLUDED
