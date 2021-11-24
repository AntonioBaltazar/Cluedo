#ifndef CARD_H_INCLUDED
#define CARD_H_INCLUDED

#include <vector>
#include <string>


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
    void card_Management();
    std::vector<Card> card_Creation(int &nb_card);
    std::vector<Card> card_Shuffle(std::vector<Card> myPackage,int nb_card);
    void card_Package_Display(std::vector<Card> myPackage);
    Card card_convert(std::string content);
    Card card_pick(std::vector<Card> &myPackage,std::string type);
};











#endif // CARD_H_INCLUDED
