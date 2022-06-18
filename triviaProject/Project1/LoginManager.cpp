#include "LoginManager.h"
#include "SqliteDataBase.h"
#include "ServerException.h"


LoginManager::LoginManager()
{
	this->m_database = nullptr;
}

LoginManager::LoginManager(IDatabase* database)
{
	this->m_database = database;
}

void LoginManager::signup(const string& username, const string& password, const string& email)
{
	
	bool doesExist = m_database->doesUserExist(username);

	if (!doesExist)
	{
		m_database->addUser(username, password, email);		
		return;
	}
	
	throw ServerException("Error: Username already exists!", ServerException::USERNAME_ALREADY_EXIST_CODE);
	
}

void LoginManager::login(const string& username, const string& password)
{
	bool doesExist = m_database->doesUserExist(username);
	bool passwordMatch = m_database->doesPasswordMatch(username, password);

	if (doesExist && passwordMatch) {
		LoggedUser newUser(username, password);
		m_loggedUsers.push_back(newUser);
		return;
	}
	
	throw ServerException("Error: Username or password Are invalid", ServerException::WRONG_USERNAME_OR_PASSWORD_CODE);
	
}

void LoginManager::logout(const string& username)
{
	
	for (auto iter = m_loggedUsers.begin(); iter != m_loggedUsers.end(); iter++)
	{
		if (iter->getName() == username)
		{
			m_loggedUsers.erase(iter);
			cout << "Logged out successfully!" << endl;
			return;
		}
	}
	
	throw ServerException("Error: no such username!", ServerException::USERNAME_NOT_FOUND);
	
}
