#pragma once
#include <iostream>
#include "IDatabase.h"
#include "Game.h"
using namespace std;


class GameManager
{

public:
	GameManager(IDatabase* database);
	Game createGame(vector<LoggedUser> users);
	void deleteGame(Game game);
	void removeUser(LoggedUser user, Game game);	
	//friend bool operator==(const Game& lhs, const Game& rhs);

private:
	static unsigned int gameId;
	IDatabase* m_database;
	vector<Game> m_games;

};