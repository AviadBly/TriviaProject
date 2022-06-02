#include "GameManager.h"

GameManager::GameManager(IDatabase* database) : m_database(database)
{
    
}

Game GameManager::createGame(string Room)
{
    vector<Question> questions = m_database->getQuestions();
    //new game
}

void GameManager::deleteGame()
{

}

void GameManager::removeUser(LoggedUser user, Game game)
{
    //TO DO, remove the user from the game the matched the given game


}
