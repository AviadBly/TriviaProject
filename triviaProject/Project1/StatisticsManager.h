#pragma once
#include <iostream>
#include <vector>
using namespace std;
#include "IDatabase.h"
#include <set>

class StatisticsManager
{

public:

	StatisticsManager(IDatabase* database);
	vector<string> getHighScore();
	vector<string> getUserStatistics(string username);

	

private:
	//set<StatsUser> users;
	IDatabase* m_database;
};