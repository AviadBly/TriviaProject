#include <iostream>
#include "SqliteDataBase.h"
#include <map>
#include <algorithm>
#include "sqlite3.h"
#include <list>
#include "LoggedUser.h"
#include <io.h>
using namespace std;


bool SqliteDataBase::open()
{

	string dbFileName = DATA_BASE_FILE_NAME;
	int doesFileExist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &db);
	if (res != SQLITE_OK) {
		db = nullptr;
		cout << "Failed to open DB" << endl;
		return false;
	}

}



int SqliteDataBase::callbackUsers(void* data, int argc, char** argv, char** azColName)
{

	list<LoggedUser>* users = (list<LoggedUser>*)data;
	LoggedUser user;

	for (int i = 0; i < argc; i++) {
		if (string(azColName[i]) == "USERNAME") {
			user.setName((argv[i]));
		}
		else if (string(azColName[i]) == "PASSWORD") {
			user.setPassword(argv[i]);
		}
		else if (string(azColName[i]) == "MAIL")
		{
			user.setMail(argv[i]);
		}

	}
	users->push_back(user);
	return 0;
}

void SqliteDataBase::sendCallBackUsers(sqlite3* db, const char* sqlStatement, list<LoggedUser>* albums)
{
	char** errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, callbackUsers, albums, errMessage);
	if (res != SQLITE_OK) {
		std::cout << res << std::endl;
		cout << "Error!" << endl;
	}



}



bool SqliteDataBase::sendToServer(sqlite3* db, const char* sqlStatement)
{
	char** errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	}
	return true;
}


void SqliteDataBase::create()
{
	
	string sqlStatement = "CREATE TABLE USERNAMES (USERNAME TEXT NOT NULL, PASSWORD TEXT NOT NULL, MAIL TEXT NOT NULL);";
	const char* newStatement = sqlStatement.c_str();
	bool check = sendToServer(db, newStatement);
	if (!check)
	{
		cout << "CREATE USERNAMES PROBLEM- EITHER EXISTS OR GENERAL ERROR" << endl;
	}
	sqlStatement = "CREATE TABLE QUESTIONS (QUESTION TEXT NOT NULL, ANSWER1 TEXT NOT NULL, ANSWER2 TEXT NOT NULL, ANSWER3 TEXT NOT NULL, ANSWER4 TEXT NOT NULL);";
	const char* newStatement = sqlStatement.c_str();
	bool check = sendToServer(db, newStatement);
	if (!check)
	{
		cout << "CREATE QUESTIONS PROBLEM- EITHER EXISTS OR GENERAL ERROR" << endl;
	}
	sqlStatement = "INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"Who was the first prime minisiter of Israel? \", \"*David Ben Gurion \", \"Benyamin Netanyhau \", \"Ariel Sharon \", \"Golda Meir \"); INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"Who is the best magshimim guide? \", \"Moshe Cohen \", \"Amir Levi \", \"*Liroy Brazilai \", \"Yuval Hamebulbal \"); INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"What is the biggest city in Israel? \", \"*Jerusalem \", \"Tel Aviv \", \"Haifa \", \"Beer Sheva \"); INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"How many years do women need to serve in the IDF? \", \"2.5 Years \", \"3 years \", \"2.2 years \", \"*2 years \"); INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"How much money goes to the IDF every year? \", \"10 Billion Shekels \", \"28 Billion Shekels \", \"44 Billion Shekels ", \"*74 Billion shekels \"); INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"When did the operation Amud Anan occour? \", \"2011 \", \"*2012 \", \"2013 \", \"*2014 \"); INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"Which country we don't have a peace agreement with? \", \"*Syria \", \"Jordan \", \"Egypt \", \"UAE \"); INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"What does IDF stand for? \", \"International data facility \", \"*Israeli defense force \", \"Israel delivers food \", \"I Dont fight \"); INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"In which war Israel wasn't prepared? \", \"6 day war \", \"Independence War \", \"Magshimim war of cyber \", \"*Yom Hakipurim War \"); INSERT INTO QUESTIONS(QUESTION, ANSWER1, ANSWER2, ANSWER3, ANSWER4) VALUES(\"Should you enlist in the IDF? \", \"No \", \"Maybe \", \"I don't know \", \"*YES \"); ";
	const char* newStatement = sqlStatement.c_str();
	bool check = sendToServer(db, newStatement);
	if (!check)
	{
		cout << "INSERT QUESTIONS PROBLEM- EITHER EXISTS OR GENERAL ERROR" << endl;
	}

}

const std::list<LoggedUser> SqliteDataBase::getUsers()
{
	list<LoggedUser>* newList = new list<LoggedUser>;
	const char* sqlStatement = "SELECT * FROM USERNAMES;";
	sendCallBackUsers(db, sqlStatement, newList);
	return *newList;
}

void SqliteDataBase::addUser(string username, string password, string mail)
{
	string values = "\"" + username + "\"" + ',' + "\"" + password + "\"" + ',' + "\"" + mail + "\"";
	string sqlStatement = "INSERT INTO USERNAMES(USERNAME,PASSWORD,MAIL) VALUES(" + values + ");";
	const char* newStatement = sqlStatement.c_str();
	bool check = sendToServer(db, newStatement);
	if (!check)
	{
		cout << "ADD USERNAME ERROR" << endl;
	}
}

bool SqliteDataBase::doesUserExist(string username)
{
	list<LoggedUser>* newList = new list<LoggedUser>;
	string sqlStatement = "SELECT * FROM USERNAMES WHERE USERNAME=\"" + username + "\";";
	const char* newStatement = sqlStatement.c_str();
	sendCallBackUsers(db, newStatement, newList);
	std::list<LoggedUser>::iterator it;
	for (it = newList->begin(); it != newList->end(); ++it)
	{
		if (it->getName() == username)
		{
			return true;
		}
	}
	return false;
}


bool SqliteDataBase::doesPasswordMatch(string username, string password)
{

	list<LoggedUser>* newList = new list<LoggedUser>;
	string sqlStatement = "SELECT * FROM USERNAMES WHERE USERNAME=\"" + username + "\";";
	const char* newStatement = sqlStatement.c_str();
	sendCallBackUsers(db, newStatement, newList);
	std::list<LoggedUser>::iterator it;
	for (it = newList->begin(); it != newList->end(); ++it)
	{
		if (it->getName() == username && it->getPassword() == password)
		{
			return true;
		}
	}
	return false;
}
