#pragma once
#define DATA_BASE_FILE_NAME "triviaDB.sqlite"
#include <iostream>
#include "Users.h"
#include "Question.h"
using namespace std;
#include <list>
class IDatabase
{
public:
	virtual ~IDatabase() = default;
	virtual void create() = 0;
	virtual void insertStats(const StatsUser& user)=0;
	virtual bool doesUserExist(string username) = 0;
	virtual bool doesPasswordMatch(string username,string password) = 0;
	virtual void addUser(string username,string password,string email) = 0;
	virtual double getPlayerAvarageAnswerTime(string username)=0;
	virtual int getNumOfCorrectAnswers(string username)=0;
	virtual int getNumOfTotalAnswers(string username)=0;
	virtual int getNumOfPlayerGames(string username)=0;
	virtual const list<StatsUser> getStatsGeneral()=0;
	virtual const vector<Question> getQuestions() = 0;

};