#include "StatisticsManager.h"
#include <string>
#include "LoggedUser.h"
#include <list>
#include <iostream>
#include <algorithm>
using namespace std;
vector<string> StatisticsManager::getHighScore()
{
	list<StatsUser> allStats;
	list<StatsUser> bestStats;
	allStats = m_database->getStatsGeneral();
	

	return vector<string>();
}

vector<string> StatisticsManager::getUserStatistics(string username)
{
	vector<string> stats;

	stats.push_back(to_string(m_database->getPlayerAvarageAnswerTime(username)));
	stats.push_back(to_string(m_database->getNumOfCorrectAnswers(username)));
	stats.push_back(to_string(m_database->getNumOfTotalAnswers(username)));
	stats.push_back(to_string(m_database->getNumOfPlayerGames(username)));


	return stats;

}
