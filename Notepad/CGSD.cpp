#include <iostream>
#include "../AnimatedElement.h"
#include "../Utils.h"
#include "Notepad.h"
#include "../Dialog.h"

// Constructors & Destructor
Notepad::Notepad() {}
Notepad::Notepad(int trslX, int trslY, int maxX, int maxY) {
    setTranslated(trslX, trslY);
    setMax(maxX, maxY);
    Dialog dTemp;
    dTemp.displayBordersPers(trslX, trslX + maxX, trslY, trslY + maxY);
}
Notepad::~Notepad() {}
// Getters
std::string Notepad::getContent() { return m_content; }
// Setters
void Notepad::setContent(std::string content) { m_content = content; }
// Methods!
void Notepad::renderTurn() {
    printAt(getTranslatedX() + 2, getTranslatedY() + 1, color("Bloc-notes", Color::White));
}
