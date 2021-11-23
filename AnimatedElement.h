#ifndef ANIMATEDELEMENT_H_INCLUDED
#define ANIMATEDELEMENT_H_INCLUDED

#include <vector>
#include "render/Square.h"

class AnimatedElement {
private:
    int m_translatedX = 0;
    int m_translatedY = 0;
    int m_maxX;
    int m_maxY;
public:
    // Constructors & Destructor
    AnimatedElement();
    AnimatedElement(int translatedX, int translatedY);
    AnimatedElement(std::string pathName);
    virtual ~AnimatedElement();

    // Getters
    int getTranslatedX() const;
    int getTranslatedY() const;
    int getMaxX() const;
    int getMaxY() const;

    // Setters
    void setTranslated(int trslX, int trslY);
    void setMax(int maxX, int maxY);
    void setTranslatedX(int translatedX);
    void setTranslatedY(int translatedY);
    void setMaxX(int maxX);
    void setMaxY(int maxY);

    // Methods
    void init(std::string pathName);
    void render(std::string pathName);
    void clearArea(int width, int height);
    void saveAsWorld(std::vector<Square>& world, std::string worldName);
};


#endif // ANIMATEDELEMENT_H_INCLUDED
