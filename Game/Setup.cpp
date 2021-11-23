#include <iostream>
#include "../Game.h"
#include <conio.h>
#include <algorithm>
#include <time.h>


void Game::askAccountOfPlayers()
{
    system("cls");
    std::string adjectives[] = {"Premier", "Second", "Troisi", "Quatri", "Cinqui", "Sixi"};
    AnimatedElement sharp(16, 11);
    AnimatedElement nb(32, 11);
    sharp.render("numbers/sharp");
    int saisie, index;
    for (int i = 0; i < getNbOfPlayers(); i++)
    {
        std::string pseudo;
        index = 0;

        // Clearing old text
        for (int j = 0; j < 3; j++)
            printAt(48, j+i, std::string(28, ' '));

        nb.render("numbers/" + std::to_string(i+1));
        gotoxy(48, 12);
        std::cout << color(adjectives[i], Color::Bright_Yellow);
        if (i > 1) std::cout << color(char(138), Color::Bright_Yellow) << color("me", Color::Bright_Yellow);
        std::cout << color(" joueur,", Color::Bright_White);
        printAt(48, 13, color("saississez votre nom :", Color::Bright_White));

        do
        {
            saisie = getInput();
            gotoxy(48, 12);

            if (((saisie >= 'a' && saisie <= 'z') || (saisie >= 'A' && saisie <= 'Z') || saisie == ' ') && index < 19)
            {
                pseudo += (char)saisie;
                printAt(48 + index, 14, std::string(1, char(saisie)));
                index++;
            }
            else if (saisie == 8 && index > 0)
            {
                pseudo.pop_back();
                index--;
                printAt(48 + index, 14, " ");
            }
        }
        while (saisie != 13 || saisie < 2);
        getPlayers().push_back(Player(pseudo, Color::Bright_Cyan));
    }
}

void Game::askNbOfPlayers()
{
    system("cls");
    int nbOfPlayers = 2;
    int saisie = -1;
    gotoxy(40, 12);
    std::cout << char(16);
    std::cout << color(" Nombre de joueurs ?", Color::Bright_White);
    gotoxy(42,13);
    std::cout << "De 2 " << char(133) <<" 6";
    AnimatedElement nb(65, 11);
    do
    {
        nb.clearArea(14, 7);
        nb.render("numbers/" + std::to_string(nbOfPlayers));
        gotoxy(42, 15);
        for (int i = 0; i < 12; i++) std::cout << " ";
        gotoxy(42, 15);
        for (int i = 0; i < nbOfPlayers; i++) std::cout << color(char(3), Color::Red) << " ";
        saisie = getInput();
        if (saisie == 72 && nbOfPlayers < 6) nbOfPlayers++;
        if (saisie == 80 && nbOfPlayers > 2) nbOfPlayers--;
    } while (saisie != 13);
    setNbOfPlayers(nbOfPlayers);
}

