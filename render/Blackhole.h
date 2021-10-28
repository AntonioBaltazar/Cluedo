#ifndef BLACKHOLE_H_INCLUDED
#define BLACKHOLE_H_INCLUDED

#include "../GraphicElement.h"
#include <vector>

class Blackhole : public GraphicElement {
private:
    std::string m_name;
    std::vector<std::vector<std::string>> m_datas;
    std::vector<std::string> m_temp;
public:
    // Constructors & Destructor
    Blackhole();
    Blackhole(int, int, std::string, std::string);
    ~Blackhole();

    // Getters
    std::string getName() const;
    std::vector<std::vector<std::string>> getDatas() const;
    std::vector<std::string> getTemp() const;

    // Setters
    void setName(std::string name);
    void setDatas(std::vector<std::vector<std::string>> datas);
    void setTemp(std::vector<std::string> temp);

    // Methods
    void render();
    void loadDatas();
    void displayDatas();
    void translateDatas();
};



#endif // BLACKHOLE_H_INCLUDED
