#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include <vector>
#include <string>

#define WEAPON 5
#define ROOM 5
#define SUSPECTS 5
#define NBCARDS 9

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

    ///Methods
    void display();
};

///Prototype
std::vector<Card> card_shuffle();
void card_package_display(std::vector<Card> MyPackage);


#endif // CARD_H_INCLUDED
