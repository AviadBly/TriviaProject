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
	vector<string> getUserStatistics(const string& username);

	StatsUser getStatsUser(const string& username);
	
	void insertStats(const StatsUser& user);

private:
	//set<StatsUser> users;
	IDatabase* m_database;
};