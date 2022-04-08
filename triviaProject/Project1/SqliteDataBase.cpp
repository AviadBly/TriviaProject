#include <iostream>
#include "SqliteDataBase.h"
#include <map>
#include <algorithm>
#include "sqlite3.h"
#include <list>
#include "User.h"
#include <io.h>
using namespace std;


bool SqliteDataBase::open()
{

	string dbFileName = "galleryDB.sqlite";
	int doesFileExist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &db);
	if (res != SQLITE_OK) {
		db = nullptr;
		cout << "Failed to open DB" << endl;
		return -1;
	}

}



int  SqliteDataBase::callbackUsers(void* data, int argc, char** argv, char** azColName)
{

	list<User>* users = (list<User>*)data;
	User user;

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

void SqliteDataBase::sendCallBackUsers(sqlite3* db, const char* sqlStatement, list<User>* albums)
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

const std::list<User> SqliteDataBase::getUsers()
{
	list<User>* newList = new list<User>;
	const char* sqlStatement = "SELECT * FROM USERNAMES;";
	sendCallBackUsers(db, sqlStatement, newList);
	return *newList;
}
void SqliteDataBase::addUser(string username, string password, string mail)
{
	string values = "\"" + username + "\"" + ',' + "\"" + password + "\"" + ',' + "\"" + password + "\"";
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
	list<User>* newList = new list<User>;
	string sqlStatement = "SELECT * FROM USERNAMES;";
	const char* newStatement = sqlStatement.c_str();
	sendCallBackUsers(db, newStatement, newList);
	std::list<User>::iterator it;
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

	list<User>* newList = new list<User>;
	string sqlStatement = "SELECT * FROM USERNAMES;";
	const char* newStatement = sqlStatement.c_str();
	sendCallBackUsers(db, newStatement, newList);
	std::list<User>::iterator it;
	for (it = newList->begin(); it != newList->end(); ++it)
	{
		if (it->getName() == username&&it->getPassword()==password)
		{
			return true;
		}
	}
	return false;
}
