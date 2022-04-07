#pragma once
#include "IDatabase.h"
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


private:
	sqlite3* db;
	static bool sendToServer(sqlite3* db, const char* sqlStatement);

 };