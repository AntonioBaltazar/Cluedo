#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include <vector>
#include <string>

#define WEAPON 5
#define ROOM 5
#define SUSPECTS 5
#define NBCARDS 10

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
std::vector<Card> card_Shuffle(std::vector<Card> myPackage);
void card_Package_Display(std::vector<Card> myPackage);
void card_Management();
std::vector<Card> card_CreationB();
Card card_CreationC(std::string content);


#endif // CARD_H_INCLUDED
