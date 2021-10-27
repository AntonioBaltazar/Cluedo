#ifndef DICE_H_INCLUDED
#define DICE_H_INCLUDED

void diceMenu();

class Dice {
private:
    int m_x;
    int m_y;
    int m_value;
    int m_wmax;
public:
    Dice();
    Dice(int, int, int);
    ~Dice();

    // Getters
    int getX() const;
    int getY() const;
    int getValue() const;
    int getWmax() const;

    // Setters
    void setX(int);
    void setY(int);
    void setValue(int);
    void setWmax(int);

    // Methods
    void random(int);
    void render();

};

#endif // DICE_H_INCLUDED
