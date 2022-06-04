#include "GameManager.h"
#include "MyException.h"

unsigned int GameManager::nextGameId;

GameManager::GameManager(IDatabase* database) : m_database(database)
{
    nextGameId = 1;
}

Game GameManager::createGame(vector<User> users)
{
    vector<Question> questions = m_database->getQuestions();
    //new game
    Game newGame(questions, users, nextGameId);
    nextGameId++;
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
            return;
        }
    }
    throw MyException("Error: no such Game ID");

}

void GameManager::removeUser(User user, Game game)
{
    //TO DO, remove the user from the game the matched the given game
    

}

//compares the games based on their id
//bool operator==(const Game& lhs, const Game& rhs)
//{
//    return lhs.getId() == rhs.getId();
//}
