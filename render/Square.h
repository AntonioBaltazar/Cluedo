#ifndef SQUARE_H_INCLUDED
#define SQUARE_H_INCLUDED

#include "../Utils.h"

enum SquareType {
    DEFAULT,
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
    std::string m_tpPath;
    std::string m_dialogPath;
    std::pair<int, int> m_coord;
public:
    // Constructors & Destructor
    Square();
    Square(int x, int y, char content, Color cl);
    Square(int x, int y, char content, Color cl, std::string tpPath, int tpX, int tpY);
    ~Square();

    // Getters
    int getX() const;
    int getY() const;
    char getContent() const;
    Color getColor() const;
    SquareType getType() const;
    std::string getTpPath() const;
    std::pair<int, int>& getCoord();
    std::string getDialogPath() const;

    // Setters
    void setX(int x);
    void setY(int y);
    void setContent(char content);
    void setColor(Color cl);
    void setType(SquareType type);
    void setTpPath(std::string tpPath);
    void setDialogPath(std::string dialogPath);
};


#endif // SQUARE_H_INCLUDED
