#pragma once
#include <iostream>
#include <vector>
using namespace std;
#include "IDatabase.h"


class StatisticsManager
{
private:
	IDatabase* m_database;
public:
	vector<string> getHighScore();
	vector<string> getUserStatistics(string username);
};