#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

class Menu {
private:
    int m_textColor = 15;
    int m_backgroundColor = 0;
public:
    Menu() {}
    ~Menu() {}

    int getTextColor() const { return m_textColor; }
    int getBackgroundColor() const { return m_backgroundColor; }

    void setTextColor(int textColor) { m_textColor = textColor; }
    void setBackgroundColor(int backgroundColor) { m_backgroundColor = backgroundColor; }

    void render();
    void displayFile(std::string fileName, int translateX, int translateY);
};


#endif // MENU_H_INCLUDED
