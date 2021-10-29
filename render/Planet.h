#ifndef PLANET_H_INCLUDED
#define PLANET_H_INCLUDED

#include "../GraphicElement.h"

class Planet : public GraphicElement {
private:
    std::string m_name;
public:
    // Constructors & Destructor
    Planet();
    Planet(int, int, std::string, std::string);
    ~Planet();

    // Getters
    std::string getName() const;

    // Setters
    void setName(std::string name);

    // Methods
    void render();
};


#endif // PLANET_H_INCLUDED
