#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED

#include "../Utils.h"

class Square {
private:
    int m_x;
    int m_y;
    char m_content;
    Color m_color;
public:
    // Constructors & Destructor
    Square();
    Square(int x, int y, char content, Color cl);
    ~Square();

    // Getters
    int getX() const;
    int getY() const;
    char getContent() const;
    Color getColor() const;

    // Setters
    void setX(int x);
    void setY(int y);
    void setContent(char content);
    void setColor(Color cl);
};


#endif // SQUARE_H_INCLUDED
