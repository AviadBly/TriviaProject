#include "GameManager.h"
#include "ServerException.h"


GameManager::GameManager(IDatabase* database) : m_database(database)
{
    
}

Game& GameManager::createGame(const vector<User>& users, unsigned int timePerQuestion, unsigned int id, unsigned int numberOfQuestions)
{
    vector<Question> questions = m_database->getQuestions(numberOfQuestions);
    for (auto& q : questions) {
        q.mixAnswers();
    }
    
    //new game
    Game newGame(questions, users, timePerQuestion, id);
    m_games.push_back(newGame);

    return m_games[m_games.size() - 1];
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

//iterates over IDs until a match is found.
Game& GameManager::joinGame(unsigned int id)
{
    for (auto iter = m_games.begin(); iter != m_games.end(); iter++)
    {
        if (iter->getId() == id)  //if ID is identical
        {          
            return *iter;
        }
    }

    throw ServerException("Error: no such Game ID", 3);
}

//Game GameManager::getGameResults(unsigned int id)
//{
//    for (auto iter = m_games.begin(); iter != m_games.end(); iter++)
//    {
//        if (iter->getId() == id)  //if ID is identical
//        {
//            for (auto& p : *iter) {
//                p.
//            }
//           
//        }
//    }
//
//    throw ServerException("Error: no such Game ID", 3);
//    return Game();
//}

//returns an iter to the wanted game
vector<Game>::iterator GameManager::getGame(const Game& game)
{
    for (auto iter = m_games.begin(); iter != m_games.end(); iter++)
    {
        if (*iter == game)  //if ID is identical
        {
            return iter;
        }
    }
    throw ServerException("Error: no such Game ID", 3);
   // return m_games.end();
}


