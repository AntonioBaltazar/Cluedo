#ifndef DICE_H_INCLUDED
#define DICE_H_INCLUDED

class Dice {
private:
    int m_x;
    int m_y;
public:
    Dice();
    Dice(int, int);
    ~Dice();

    // Getters
    int getX() const;
    int getY() const;

    // Setters
    void setX(int);
    void setY(int);
};

#endif // DICE_H_INCLUDED
