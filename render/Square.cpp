#include <iostream>
#include "../Utils.h"
#include "Square.h"

// Constructors & Destructor
Square::Square() {}
Square::Square(int x, int y, char content, Color cl)
    : m_x(x), m_y(y), m_content(content), m_color(cl), m_type(SquareType::WALL) {}
Square::Square(int x, int y, char content, Color cl, std::string tpPath, int tpX, int tpY)
    : m_x(x), m_y(y), m_content(content), m_color(cl), m_type(SquareType::TELEPORTER), m_tpPath(tpPath)
{
    getCoord().first = tpX;
    getCoord().second = tpY;
}

Square::~Square() {}

// Getters
int Square::getX() const { return m_x; }
int Square::getY() const { return m_y; }
char Square::getContent() const { return m_content; }
Color Square::getColor() const { return m_color; }
SquareType Square::getType() const { return m_type; }
std::string Square::getTpPath() const { return m_tpPath; }
std::pair<int, int>& Square::getCoord() { return m_coord; }

// Setters
void Square::setX(int x) { m_x = x; }
void Square::setY(int y) { m_y = y; }
void Square::setContent(char content) { m_content = content; }
void Square::setColor(Color cl) { m_color = cl; }
void Square::setType(SquareType type) { m_type = type; }
void Square::setTpPath(std::string tpPath) { m_tpPath = tpPath; }
