#pragma once
#include "IDatabase.h"
#include <list>
#include "Users.h"
#include "sqlite3.h"
#include <iostream>
using namespace std;
class SqliteDataBase :public  IDatabase
{
public:
	virtual ~SqliteDataBase() = default;
	virtual void create() ;
	virtual bool doesUserExist(string username) ;
	virtual void insertStats(const StatsUser& user);
	void insertQuestion(const Question question);
	virtual bool doesPasswordMatch(string username, string password) ;
	const std::list<StatsUser> getStats(string username);
	const std::list<StatsUser> getStatsGeneral();
	virtual void addUser(string username,string password,string mail) ;
	const std::list<LoggedUser> getUsers();
	/***************************************************************************/

	virtual double getPlayerAvarageAnswerTime(string username) ;
	virtual int getNumOfCorrectAnswers(string username) ;
	virtual int getNumOfTotalAnswers(string username) ;
	virtual int getNumOfPlayerGames(string username) ;

	/******************************************************/
	virtual const vector<Question> getQuestions(unsigned int numberOfQuestion);

	bool open();

private:
	sqlite3* db;

	static bool sendToServer(sqlite3* db, const char* sqlStatement);
	void sendCallBackUsers(sqlite3* db, const char* sqlStatement, list<LoggedUser>* albums);
	static int callbackUsers(void* data, int argc, char** argv, char** azColName);
	static int callbackStats(void* data, int argc, char** argv, char** azColName);
	void sendCallBackStats(sqlite3* db, const char* sqlStatement, list<StatsUser>* albums);
	static int callbackQuestions(void* data, int argc, char** argv, char** azColName);
	void sendCallBackQuestions(sqlite3* db, const char* sqlStatement, vector<Question>* questions);
 };