#ifndef NOTEPAD_H_INCLUDED
#define NOTEPAD_H_INCLUDED

class Notepad : public AnimatedElement {
private:
    std::string m_content;
public:
    // Constructors & Destructor
    Notepad();
    Notepad(int trslX, int trslY, int maxX, int maxY);
    ~Notepad();
    // Getters
    std::string getContent();
    // Setters
    void setContent(std::string content);
    void renderTurn();
    std::string open(std::string str);
};


#endif // NOTEPAD_H_INCLUDED
