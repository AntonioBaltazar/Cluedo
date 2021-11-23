#ifndef DICE_H_INCLUDED
#define DICE_H_INCLUDED

#include "../AnimatedElement.h"

void diceMenu();

class Dice : public AnimatedElement{
private:
    int m_value;
public:
    Dice();
    Dice(int trslX, int trslY, int maxX, int maxY);
    ~Dice();
    // Methods
    int throwing();
};

#endif // DICE_H_INCLUDED
