#include <iostream>
#include <string>
#include "Blackhole.h"

// Constructors & Destructor
Blackhole::Blackhole() {}
Blackhole::Blackhole(int x, int y, std::string path, std::string name) : GraphicElement(x, y, path), m_name(name) {}
Blackhole::~Blackhole() {}

// Getters
std::string Blackhole::getName() const { return m_name; }
std::vector<std::vector<std::string>> Blackhole::getDatas() const { return m_datas; }

// Setters
void Blackhole::setName(std::string name) { m_name = name; }
void Blackhole::setDatas(std::vector<std::vector<std::string>> datas) { m_datas = datas; }

// Methods
void Blackhole::render() { GraphicElement::render(""); }

void Blackhole::loadDatas()
{
    setDatas(GraphicElement::render(""));
}

void Blackhole::translateDatas()
{

}

