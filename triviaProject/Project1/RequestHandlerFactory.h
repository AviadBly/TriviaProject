#pragma once
#include <vector>
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoggedUser.h"
#include "LoginRequestHandler.h"

class RequestHandlerFactory {

public:
	
	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManger();

private:
	LoginManager m_loginManager;
	IDatabase* m_database;
};