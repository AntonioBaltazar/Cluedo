#include <iostream>
#include "../Utils.h"
#include "Square.h"

// Constructors & Destructor
Square::Square() {}
Square::Square(int x, int y, char content, Color cl) : m_x(x), m_y(y), m_content(content), m_color(cl) {}
Square::~Square() {}

// Getters
int Square::getX() const { return m_x; }
int Square::getY() const { return m_y; }
char Square::getContent() const { return m_content; }
Color Square::getColor() const { return m_color; }

// Setters
void Square::setX(int x) { m_x = x; }
void Square::setY(int y) { m_y = y; }
void Square::setContent(char content) { m_content = content; }
void Square::setColor(Color cl) { m_color = cl; }
