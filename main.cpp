#include <iostream>
#include <windows.h>
#include "Utils.h"
#include "Card.h"

int main()
{
    activateVirtualTerminal();
    std::cout << "Hello world!" << std::endl;
    std::cout << color("woww", Color::Bright_Blue) << " c'est super" << color(" c'est rouge", Color::Magenta)<<std::endl;



    ///Card Creation & Mixture
    std::vector<Card> MyPackage;
    MyPackage = card_shuffle(); //Mélange
    card_package_display(MyPackage); //Affichage

    return 0;
}
