#ifndef DICE_H_INCLUDED
#define DICE_H_INCLUDED

#include "../AnimatedElement.h"

void diceMenu();

class Dice : public AnimatedElement{
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
