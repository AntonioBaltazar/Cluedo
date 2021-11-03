#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED

#include "../Utils.h"

enum SquareType {
    WALL,
    TELEPORTER,
    NPC
};

class Square {
private:
    int m_x;
    int m_y;
    char m_content;
    Color m_color;
    SquareType m_type;
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
    SquareType getType() const;

    // Setters
    void setX(int x);
    void setY(int y);
    void setContent(char content);
    void setColor(Color cl);
    void setType(SquareType type);
};


#endif // SQUARE_H_INCLUDED
