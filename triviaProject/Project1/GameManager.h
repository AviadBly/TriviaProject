#pragma once
#include <iostream>
#include "IDatabase.h"
#include "Game.h"
using namespace std;


class GameManager
{
private:
	IDatabase* m_database;
	vector<Game> m_games;

public:
	Game createGame(string Room);
	void deleteGame();
};