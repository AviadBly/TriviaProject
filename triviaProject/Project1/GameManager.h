#pragma once
#include <iostream>
#include "IDatabase.h"
#include "Game.h"
using namespace std;


class GameManager
{

public:
	GameManager(IDatabase* database);
	Game& createGame(const vector<User>& users, unsigned int timePerQuestion, unsigned int id, unsigned int numberOfQuestions);
	void deleteGame(const Game& game);
	void removeUser(const User& user, const Game& game);
	//friend bool operator==(const Game& lhs, const Game& rhs);
	
	Game& joinGame(unsigned int id);
	
private:

	IDatabase* m_database;
	vector<Game> m_games;

	vector<Game>::iterator getGame(const Game& game);
};