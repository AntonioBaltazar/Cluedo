#include <iostream>
#include "Dice.h"

int Dice::getX() const { return m_x; }
int Dice::getY() const { return m_y; }
int Dice::getValue() const { return m_value; }

void Dice::setX(int x) { m_x = x; }
void Dice::setY(int y) { m_y = y; }
void Dice::setValue(int value) { m_value = value; }

void Dice::random(int maxValue = 6) {
    setValue(rand() % maxValue + 1);
}
