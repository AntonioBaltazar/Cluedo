#ifndef GRAPHICELEMENT_H_INCLUDED
#define GRAPHICELEMENT_H_INCLUDED
#include <vector>

class GraphicElement {
protected:
    int m_x;
    int m_y;
    int m_maxWidth;
    std::string m_path;
public:
    //Constructors & Destructor
    GraphicElement();
    GraphicElement(int, int, std::string);
    ~GraphicElement();

    //Getters
    int getX() const;
    int getY() const;
    int getMaxWidth() const;
    std::string getPath() const;

    //Setters
    void setX(int x);
    void setY(int y);
    void setMaxWidth(int maxWidth);
    void setPath(std::string path);

    //Methods
    std::vector<std::vector<std::string>> render();
    std::vector<std::vector<std::string>> render(std::string extravalue);
};


#endif // GRAPHICELEMENT_H_INCLUDED
