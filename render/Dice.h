#ifndef DICE_H_INCLUDED
#define DICE_H_INCLUDED

void diceMenu();

class Dice {
private:
    int m_x;
    int m_y;
    int m_value;
public:
    Dice();
    Dice(int, int, int);
    ~Dice();

    // Getters
    int getX() const;
    int getY() const;
    int getValue() const;

    // Setters
    void setX(int);
    void setY(int);
    void setValue(int);

    // Methods
    void random(int);
    void render();

};

#endif // DICE_H_INCLUDED
