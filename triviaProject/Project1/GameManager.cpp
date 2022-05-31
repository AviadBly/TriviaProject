#include "GameManager.h"

GameManager::GameManager(IDatabase* database) : m_database(database)
{
    
}

Game GameManager::createGame(string Room)
{
    return Game();
}

void GameManager::deleteGame()
{
}

void GameManager::removeUser(LoggedUser user, Game game)
{
    //TO DO, remove the user from the game the matched the given game


}
