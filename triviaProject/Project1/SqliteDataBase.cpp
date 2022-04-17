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
		cout << "CREATE PROBLEM- EITHER EXISTS OR GENERAL ERROR" << endl;
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
