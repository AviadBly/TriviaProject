#include "GameManager.h"
#include "MyException.h"
GameManager::GameManager(IDatabase* database) : m_database(database)
{
    gameId = 1;
}

Game GameManager::createGame(string Room)
{
    vector<Question> questions = m_database->getQuestions();
    //new game
    Game newGame(questions, gameId);
    gameId++;
    return newGame;
}

void GameManager::deleteGame(Game game)
{
    for (auto iter = m_games.begin(); iter != m_games.end(); iter++)
    {
        if (iter->getId() == game.getId())
        {
            m_games.erase(iter);
            cout << "Game Deleted" << endl;
            break;
        }
    }
    throw MyException("Error: no such Game ID");

}

//void GameManager::removeUser(LoggedUser user, Game game)
//{
//    //TO DO, remove the user from the game the matched the given game
//    
//
//}

//bool operator==(const Game& lhs, const Game& rhs)
//{
//    if (lhs == rhs)
//    {
//        return true;
//    }
//    return false;
//}
