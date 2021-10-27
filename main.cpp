#include <iostream>
#include <windows.h>
#include "Utils.h"
#include "Card.h"

int main()
{
    activateVirtualTerminal();
    std::cout << "Hello world!" << std::endl;
    std::cout << color("woww", Color::Bright_Blue) << " c'est super" << color(" c'est rouge", Color::Magenta)<<std::endl;

    std::vector<Card> MyPackage;

    MyPackage = card_shuffle();

    card_package_display(MyPackage);

    return 0;
}
