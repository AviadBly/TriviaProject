#include "StatisticsManager.h"
#include <string>
#include <list>
#include <iostream>
#include <algorithm>


using namespace std;


StatisticsManager::StatisticsManager(IDatabase* database)
{
	this->m_database = database;

	
}

void StatisticsManager::insertStats(const StatsUser& user)
{
	m_database->insertStats(user);
	
}


vector<string> StatisticsManager::getHighScore()
{
	//confusing function but don't blame me because instructions were confusing too >:( !!
	
	int* top3 = new int[3];
	list<StatsUser> allStats = m_database->getStatsGeneral();
	vector<int> scores;
	
	//get only the scores
	for (auto iter = allStats.begin(); iter != allStats.end(); iter++)
	{
		scores.push_back(iter->getCorrect());
	}
	if (scores.size() < 3)
	{
		return vector<string>();
	}

	//get the 3 highest scores
	for (int i = 0; i < 3; i++)
	{
		
		top3[i]=(*max_element(scores.begin(), scores.end()));
		int max = *max_element(scores.begin(), scores.end());
		for (auto iter = scores.begin(); iter != scores.end(); iter++)
		{
			if (*iter == max)
			{
				scores.erase(iter);
				break;
			}
		}
	}

	vector<string> top3names;
	//3 times, match the score to the name and insert the name to a final vector.
	for (auto iter = allStats.begin(); iter != allStats.end(); iter++)
	{
		if (iter->getCorrect() == top3[0])
		{
			top3names.push_back(iter->getName());
			break;
		}
	}
	for (auto iter = allStats.begin(); iter != allStats.end(); iter++)
	{
		if (iter->getCorrect() == top3[1])
		{
			top3names.push_back(iter->getName());
			break;
		}
	}
	for (auto iter = allStats.begin(); iter != allStats.end(); iter++)
	{
		if (iter->getCorrect() == top3[2])
		{
			top3names.push_back(iter->getName());
			break;
		}
	}


	return top3names;
}

vector<string> StatisticsManager::getUserStatistics(const string& username)
{
	vector<string> stats;

	stats.push_back(to_string(m_database->getPlayerAvarageAnswerTime(username)));
	stats.push_back(to_string(m_database->getNumOfCorrectAnswers(username)));
	stats.push_back(to_string(m_database->getNumOfTotalAnswers(username)));
	stats.push_back(to_string(m_database->getNumOfPlayerGames(username)));


	return stats;

}

StatsUser StatisticsManager::getStatsUser(const string& username)
{
	StatsUser user(username, 
		m_database->getPlayerAvarageAnswerTime(username),
		m_database->getNumOfCorrectAnswers(username),
		m_database->getNumOfTotalAnswers(username),
		m_database->getNumOfPlayerGames(username));


	return user;

}


bool StatisticsManager::CreateQuestion(string question, string answer1, string answer2, string answer3, string correct)
{
	correct = "*" + correct;
	
	if (m_database->insertQuestion( question, answer1, answer2, answer3, correct))
	{
		return true;
	}
	return false;

}