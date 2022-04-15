#pragma once
#include <vector>
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoggedUser.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

class RequestHandlerFactory {

public:
	RequestHandlerFactory(IDatabase* database);

	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManger();

	MenuRequestHandler* createMenuRequestHandler();

private:
	LoginManager m_loginManager;
	IDatabase* m_database;
};