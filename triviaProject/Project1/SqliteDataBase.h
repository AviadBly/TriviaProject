#pragma once
#include "IDatabase.h"
#include <list>
#include "User.h"
#include "sqlite3.h"
#include <iostream>
using namespace std;
class SqliteDataBase :public  IDatabase
{
public:
	virtual ~SqliteDataBase() = default;
	virtual void create() ;
	virtual bool doesUserExist(string username) ;
	virtual bool doesPasswordMatch(string username, string password) ;
	virtual void addUser(string username,string password,string mail) ;
	const std::list<User> getUsers();

	bool open();
private:
	sqlite3* db;
	static bool sendToServer(sqlite3* db, const char* sqlStatement);
	void sendCallBackUsers(sqlite3* db, const char* sqlStatement, list<User>* albums);
	static int callbackUsers(void* data, int argc, char** argv, char** azColName);
 };