#include <iostream>
#include <windows.h>
#include <vector>
#include <fstream>
#include <conio.h>


#include "../Player.h"
#include "../Game.h"
#include "../Utils.h"


void Game::setNbCard( int nbCard)   { m_nbCard = nbCard; }

///Create the in-game packages
void Game::setGamePackage()
 {
    Card temp;
    int nbCard;
    m_gamePackage = temp.card_Creation(nbCard);
    m_gamePackage = temp.card_Shuffle(getGamePackage(),nbCard);
//    temp.card_Package_Display(m_gamePackage);
    setNbCard(nbCard);
 }

///Gives one card of each type to every player
void Game::cardDistrib()
{
     std::vector<Player>::iterator it;

    for(it = m_players.begin(); it != m_players.end();it++)
       it->create_player_package(m_gamePackage);

}

///Creates one as a reference and the one is for the game
void Game::setAllPackages()
{
    setGamePackage();
    m_allCards = getGamePackage();
}

std::vector<Card> Game::getGamePackage()const    {  return m_gamePackage;}
std::vector<Card> Game::getAllCard()const    {  return m_allCards;}

///Displays every card of a package
void Game::displayPackage(std::vector<Card> Gamepackage)
{
    Card temp;

    temp.card_Package_Display(Gamepackage);
}
