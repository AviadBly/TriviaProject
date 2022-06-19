#pragma once
#include <string>
#include <vector>
#include "IDatabase.h"
#include "Users.h"

class LoginManager {

public:	
	LoginManager();
	LoginManager(IDatabase* database);


	void signup(const string& username, const string& password, const string& email);
	void login(const string& username, const string& password);
	void logout(const string& username);

private:
	vector<LoggedUser> m_loggedUsers;
	IDatabase* m_database;
};