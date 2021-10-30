#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

class Menu {
public:
    Menu() {}
    ~Menu() {}

    void render();
    void displayFile(std::string fileName);
};


#endif // MENU_H_INCLUDED
