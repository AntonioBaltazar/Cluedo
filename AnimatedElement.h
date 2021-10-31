#ifndef ANIMATEDELEMENT_H_INCLUDED
#define ANIMATEDELEMENT_H_INCLUDED

class AnimatedElement {
private:
    int m_translatedX;
    int m_translatedY;
public:
    // Constructors & Destructor
    AnimatedElement();
    AnimatedElement(int translatedX, int translatedY);
    ~AnimatedElement();

    // Getters
    int getTranslatedX() const;
    int getTranslatedY() const;

    // Setters
    void setTranslatedX(int translatedX);
    void setTranslatedY(int translatedY);

    // Methods
    void render(std::string pathName);
    void clearArea(int width, int height);
};


#endif // ANIMATEDELEMENT_H_INCLUDED
