#pragma once
#include <vector>
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoggedUser.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"

class LoginRequestHandler;
<<<<<<< HEAD
class MenuRequestHandler;
=======
<<<<<<< HEAD
=======
class MenuRequestHandler;
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71

class RequestHandlerFactory {

public:
	RequestHandlerFactory(IDatabase* database);

	LoginRequestHandler* createLoginRequestHandler();
	LoginManager& getLoginManger();

	MenuRequestHandler* createMenuRequestHandler();

private:
	LoginRequestHandler* m_loginRequestHandler; //this is against the uml but it way better
	MenuRequestHandler* m_menuRequestHandler; //this is against the uml but it way better
	LoginManager m_loginManager;
	IDatabase* m_database;
};