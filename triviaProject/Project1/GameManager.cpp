#include "GameManager.h"
#include "MyException.h"


GameManager::GameManager(IDatabase* database) : m_database(database)
{
    
}

Game GameManager::createGame(vector<User> users, unsigned int timePerQuestion)
{
    vector<Question> questions = m_database->getQuestions();
    //new game
    Game newGame(questions, users, timePerQuestion);

    return newGame;
}

void GameManager::deleteGame(const Game& game)
{
    auto wantedGame = getGame(game);
    m_games.erase(wantedGame);
    cout << "Game Deleted" << endl;

}

void GameManager::removeUser(const User& user, const Game& game)
{  
    auto wantedGame = getGame(game);
    wantedGame->removePlayer(user);
}

//returns an iter to the wanted game
auto GameManager::getGame(const Game& game)
{
    for (auto iter = m_games.begin(); iter != m_games.end(); iter++)
    {
        if (*iter == game)  //if ID is identical
        {
            return iter;
        }
    }
    throw MyException("Error: no such Game ID");
   // return m_games.end();
}

//compares the games based on their id
//bool operator==(const Game& lhs, const Game& rhs)
//{
//    return lhs.getId() == rhs.getId();
//}
