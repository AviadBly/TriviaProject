#include "StatisticsManager.h"
#include <string>
#include "LoggedUser.h"
#include <list>
#include <iostream>
#include <algorithm>
using namespace std;
vector<string> StatisticsManager::getHighScore()
{
	//confusing function but don't blame me because instructions were confusing too >:( !!
	list<StatsUser> allStats;
	vector<int> top5;
	allStats = m_database->getStatsGeneral();
	vector<int> scores;
	
	//get only the scores
	for (auto iter = allStats.begin(); iter != allStats.end(); iter++)
	{
		scores.push_back(iter->getCorrect());
	}

	//get the 5 highest scores
	for (int i = 0; i < 5; i++)
	{
		top5.push_back(*max_element(scores.begin(), scores.end()));
	}

	vector<string> top5names;
	//5 times, match the score to the name and insert the name to a final vector.
	for (int i = 0; i < 5; i++)
	{
		for (auto iter = allStats.begin(); iter != allStats.end(); iter++)
		{
			if (iter->getCorrect() == top5[i])
			{
				top5names.push_back(iter->getName());
			}
		}
	}
	

	return top5names;
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
