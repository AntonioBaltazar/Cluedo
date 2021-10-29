#ifndef GRAPHICELEMENT_H_INCLUDED
#define GRAPHICELEMENT_H_INCLUDED
#include <vector>

class GraphicElement {
protected:
    int m_x;
    int m_y;
    int m_maxWidth;
    std::vector<std::vector<std::string>> m_datas;
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
    std::vector<std::vector<std::string>>& getDatas();

    //Setters
    void setX(int x);
    void setY(int y);
    void setMaxWidth(int maxWidth);
    void setPath(std::string path);
    void setDatas(std::vector<std::vector<std::string>> datas);

    //Methods
    void loadDatasFromFile();
    void loadDatasFromFile(std::string extravalue);
    void render();
};


#endif // GRAPHICELEMENT_H_INCLUDED
