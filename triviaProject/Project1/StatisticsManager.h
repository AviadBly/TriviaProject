#pragma once
#include <iostream>
#include <vector>
using namespace std;
#include "IDatabase.h"


class StatisticsManager
{

public:

	StatisticsManager(IDatabase* database);
	vector<string> getHighScore();
	vector<string> getUserStatistics(string username);

private:
	IDatabase* m_database;
};