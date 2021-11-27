#include <iostream>
#include "../Game.h"
#include <conio.h>
#include <algorithm>
#include <time.h>

void Game::clearGlobal()
{
    int winX(120), winY(30);
    std::vector<std::pair<int, int>> elementSlices;
    for (int i = 0; i < winY; i++)
    {
        // Getting element's slices
        elementSlices.clear();
        for (const auto& element : getElements())
            if (i >= element->getTranslatedY() && i <= element->getTranslatedY() + element->getMaxY() + 1)
                elementSlices.push_back(std::pair<int, int>(element->getTranslatedX(), element->getMaxX() + 1));

        int stringX(0);
        // Sort vector
        sort(elementSlices.begin(), elementSlices.end());

        // Printing slices of spaces char
        for (const auto& slice : elementSlices)
        {
            printAt(stringX, i, std::string(slice.first - stringX, ' '));
            stringX += slice.first + slice.second;
        }
        if (stringX < 120)
            printAt(stringX, i, std::string((stringX == 0 ? winX : 120 - stringX), ' '));
    }
}

void Game::showStars(AnimatedElement world, Player p)
{
    // Affichage d'étoile aléatoire
    // Ctrnt : Dans l'arrière plan
    srand(NULL);
    int nbOfStars(15);
    std::vector<char> shapesStars({'*', '.', '`'});
    std::vector<Color> colorsStars({Color::White, Color::Bright_Yellow, Color::Bright_White, Color::Bright_Black, Color::Bright_Cyan});
    // Add world to not print start on planet
    AnimatedElement aeTemp = world;
    std::vector<AnimatedElement> temp;
    for (auto& el : getElements())
        temp.push_back(*el);

    aeTemp.setTranslatedX(60 - p.getX());
    aeTemp.setTranslatedY(13 - p.getY());
    temp.push_back(aeTemp);

    for (int i = 0; i < 176; i++)
    {
        int x, y;
        bool found(false);
        do
        {
            x = rand() % 125;
            y = rand() % 30;

            bool freeSlot(true);
            for (const auto& el : temp) {
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
