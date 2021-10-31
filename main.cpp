#include <iostream>
#include <windows.h>

#include "render/Dice.h"
#include "Utils.h"
#include "Card/Card.h"
#include "Script/Script.h"
#include "ConsoleHandler.h"

int main()
{
    // Resize console, hide cursor, get title & allow colors
    initConsole("Cluedoremifasollasi");

    int saisie = 0;
    Script myScript("Tonio","Uranus","spoon");

    do
    {
        system("cls");
        std::cout << color("Que voulez-vous faire ?", Color::Red) << std::endl;
        std::cout << color("1.", Color::Bright_Red) << " Emma" << std::endl;
        std::cout << color("2.", Color::Bright_Red) << " Tonio" << std::endl;
        std::cout << color("3.", Color::Bright_Red) << " Martin (bg le gars)  M'ouais" << std::endl;
        std::cout << color("4.", Color::Bright_Red) << " Fini la seance de test" << std::endl;
        std::cin >> saisie;
        switch (saisie)
        {
            case 1:
                ///Appel fct Emma
                break;
            case 2:
                ///Appel fct Tonio
                //Card Package Creation, Mixture and dislpay
                //card_Management();
                script_Creation();
                break;
            case 3:
                ///Appel fct Martin
                diceMenu();
                break;
            default: break;
        }
    } while (saisie != 4);


    return 0;
}
