#ifndef DICE_H_INCLUDED
#define DICE_H_INCLUDED

#include "../GraphicElement.h"

void diceMenu();

class Dice : public GraphicElement {
private:
    int m_value;
public:
    Dice();
    Dice(int, int, std::string, int);
    ~Dice();

    // Getters
    int getValue() const;

    // Setters
    void setValue(int);

    // Methods
    void random(int);
    void throwing();
    void render();
};

#endif // DICE_H_INCLUDED
