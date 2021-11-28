#include <iostream>
#include <fstream>
#include "../Game.h"
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <time.h>
#include <vector>

void Game::saveCurrentGame()
{
    Game temp = *this;

    std::ofstream f("save.txt", std::ios::binary);
    f.write((char*)&temp, sizeof(Game));
    f.close();
}

void Game::lunchFromSave()
{
    /*std::fstream file;
    std::cout<<"aie";
    file.open("save.dat", std::ios::out|std::ios::binary);
    file.write((char*)this, sizeof(Game));
    file.close();*/
    /*FILE *fp;
    Game temp;
    fp = fopen("save.dat", "rb");

    if (fp == NULL)
        exit(1);

    while (fread(&temp, sizeof(Game), 1, fp) != NULL);
    for (auto& p : temp.getPlayers())
        std::cout<<p.getName();
    std::cout << "debugging";
    while(true);
    fclose(fp);*/
    Game temp;
    std::ifstream f("save.txt", std::ios::binary);
    while(!f.eof())
        f.read((char*)&temp, sizeof(Game));

    for (auto& p : temp.getPlayers())
        std::cout << p.getName();
    while(1);
    f.close();
}
