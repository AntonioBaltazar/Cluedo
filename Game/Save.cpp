#include <iostream>
#include <fstream>
#include "../Game.h"
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <time.h>
#include <vector>

 std::istream& load(std::istream& is){
    size_t vsize;
    if(is.read((char*)&vsize, sizeof(vsize))) {
        first_vector.resize(vsize);
        is.read((char*)first_vector.data(), vsize*sizeof(float));
    }
    return is;
}
std::ostream& save(std::ostream& os){
    size_t vsize=first_vector.size();
    os.write((char*)&vsize, sizeof(vsize));
    os.write((char*)first_vector.data(), vsize*sizeof(float));
    return os;
}

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
