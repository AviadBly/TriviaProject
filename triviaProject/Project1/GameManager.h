#pragma once
#include <iostream>
#include "IDatabase.h"
#include "Game.h"
using namespace std;


class GameManager
{

public:
	GameManager(IDatabase* database);
	Game createGame(vector<User> users);
	void deleteGame(Game game);
	void removeUser(User user, Game game);
	//friend bool operator==(const Game& lhs, const Game& rhs);
	
private:
	static unsigned int nextGameId;
	IDatabase* m_database;
	vector<Game> m_games;

};