#include <iostream>
#include <string>
#include "Planet.h"

// Constructors & Destructor
Planet::Planet() {}
Planet::Planet(int x, int y, std::string path, std::string name) : GraphicElement(x, y, path), m_name(name) {}
Planet::~Planet() {}

// Getters
std::string Planet::getName() const { return m_name; }

// Setters
void Planet::setName(std::string name) { m_name = name; }

// Methods
void Planet::render() { GraphicElement::render(); }
