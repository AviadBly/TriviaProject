#pragma once
#include <iostream>
#include "IDatabase.h"
#include "Game.h"
using namespace std;


class GameManager
{

public:
	GameManager(IDatabase* database);
	Game createGame(string Room);
	void deleteGame();
	void removeUser(LoggedUser user, Game game);	//TO do

private:
	IDatabase* m_database;
	vector<Game> m_games;

};