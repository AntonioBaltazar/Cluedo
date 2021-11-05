#ifndef DICE_H_INCLUDED
#define DICE_H_INCLUDED

#include "../GraphicElement.h"

void diceMenu();

class Dice {
private:
    int m_value;
public:
    Dice();
    Dice(int);
    ~Dice();

    // Getters
    int getValue() const;

    // Setters
    void setValue(int);

    // Methods
    void random(int);
    int throwing();
};

#endif // DICE_H_INCLUDED
