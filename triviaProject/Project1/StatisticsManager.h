#pragma once
#include <iostream>
#include "IDatabase.h"
#include <vector>
using namespace std;

class StatisticsManager
{
public:
	vector<string> getHighScore();
	vector<string> getUserStatistics(string username);
private:

	IDatabase* m_database;
};