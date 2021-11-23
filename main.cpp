#include <iostream>
#include <windows.h>

#include "render/Dice.h"
#include "Utils.h"
#include "Card/Card.h"
#include "Script/Script.h"
#include "ConsoleHandler.h"
#include "Game.h"
#include "scenes/Menu.h"

int main()
{
    // Resize console, hide cursor, get title & allow colors
    initConsole("Cluedo - Ne vous laissez pas enculer");

    int saisie = 0;
    Card package;

    do
    {
        std::cout << color("Que voulez-vous faire ?", Color::Red) << std::endl;
        std::cout << color("1.", Color::Bright_Red) << " Emma" << std::endl;
        std::cout << color("2.", Color::Bright_Red) << " Tonio" << std::endl;
        std::cout << color("3.", Color::Bright_Red) << " Martin (bg le gars)  M'ouais" << std::endl;
        std::cout << color("4.", Color::Bright_Red) << " Lancer une partie" << std::endl;
        std::cout << color("5.", Color::Bright_Red) << " Fini la seance de test" << std::endl;
        std::cin >> saisie;
        Game g;
        Menu m;
        Player p;
        switch (saisie)
        {
            case 1:
                ///Appel fct Emma
                m.launch();
                //p.actionMenu();
                break;
            case 2:
                ///Appel fct Tonio
                g.cardDistrib();
                break;
            case 3:
                ///Appel fct Martin
                diceMenu();
                break;
            case 4:
                g.start();
                break;
            default: break;
        }
    } while (saisie != 5);


    return 0;
}
