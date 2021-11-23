#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <conio.h>
#include "../World.h"
#include "../render/Dice.h"
#include "../Player.h"
#include "../Game.h"
#include "../AnimatedElement.h"
#include "../Utils.h"


void Game::cardDistrib()
{
     std::vector<Player>::iterator it;

    for(it = m_players.begin(); it != m_players.end();it++)
       it->create_player_package(m_gamePackage);

}
