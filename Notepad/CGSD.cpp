#include <iostream>
#include "../AnimatedElement.h"
#include "../Utils.h"
#include "Notepad.h"

// Constructors & Destructor
Notepad::Notepad() {}
Notepad::Notepad(int trslX, int trslY, int maxX, int maxY) {}
Notepad::~Notepad() {}
// Getters
std::string Notepad::getContent() { return m_content; }
// Setters
void Notepad::setContent(std::string content) { m_content = content; }
// Methods!
void Notepad::renderTurn() {

}
