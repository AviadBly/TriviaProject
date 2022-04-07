#include <iostream>
#include "SqliteDataBase.h"
#include <map>
#include <algorithm>
#include "sqlite3.h"
using namespace std;


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

bool SqliteDataBase::doesUserExist(string username)
{
	string sqlStatement = "SELECT * FROM USERNAMES WHERE USERNAME=\""+username+"\";";
	const char* newStatement = sqlStatement.c_str();
	//
}