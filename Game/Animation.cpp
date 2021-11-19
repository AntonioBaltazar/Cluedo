#include <iostream>
#include "../Game.h"
#include "time.h"

void Game::showStars()
{
    // Affichage d'étoile aléatoire
    // Ctrnt : Dans l'arrière plan

    srand(NULL);
    int nbOfStars(15);
    std::vector<char> shapesStars({'*', '.', '°', '@'});
    std::vector<Color> colorsStars({Color::White, Color::Bright_Yellow, Color::Bright_White, Color::Bright_Black});

    for (int i = 0; i < 15; i++)
    {
        int x, y;
        bool found(false);
        do
        {
            x = rand() % 120;
            y = rand() % 25;

            bool freeSlot(true);
            for (const auto& el : getElements()) {
                if (el.getTranslatedX() <= x && x <= el.getTranslatedX() + el.getMaxX() &&
                        el.getTranslatedY() <= y && y <= el.getTranslatedY() + el.getMaxY())
                {
                    freeSlot = false;
                    break;
                }
            }
            found = freeSlot;
        } while(!found);
        printAt(x, y, color(shapesStars[rand() % shapesStars.size()], colorsStars[rand() % colorsStars.size()]));
    }

}
