#include <iostream>
#include <windows.h>
#include "Utils.h"
#include "Card.h"

int main()
{
    activateVirtualTerminal();
    int saisie;
    do
    {
        std::cout << color("Que voulez-vous faire ?", Color::Red) << std::endl;
        std::cout << color("1.", Color::Bright_Red) << " Emma" << std::endl;
        std::cout << color("2.", Color::Bright_Red) << " Tonio" << std::endl;
        std::cout << color("3.", Color::Bright_Red) << " Martin (bg le gars)" << std::endl;
        std::cin >> saisie;
        switch (saisie)
        {
            case 1:
                //Appel fct Emma
                break;
            case 2:
                //Appel fct Tonio
                break;
            case 3:
                //Appel fct Martin
                break;
            default: break;
        }
    } while (saisie > 0 && saisie < 4);

    std::vector<Card> MyPackage;
    MyPackage = card_shuffle();

    card_package_display(MyPackage);

    return 0;
}
