#pragma once
#include <string>
#include <vector>
#include "IDatabase.h"
#include "LoggedUser.h"
#include "LoggedUser.h"

class LoginManager {

public:	
	LoginManager();
	LoginManager(IDatabase* database);

	//to do
	void signup(const std::string username, const std::string password, const std::string email);
	void login(const std::string username, const std::string password);
	void logout(const std::string username);

private:
	std::vector<LoggedUser> m_loggedUsers;
	IDatabase* m_database;
};