#include "RequestHandlerFactory.h"


RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) {
	this->m_database = database;
	this->m_loginManager = LoginManager(database);
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	//not sure if its correct
	LoginRequestHandler loginRequestHandler(getLoginManger(), *this);

	return &loginRequestHandler;
}

LoginManager& RequestHandlerFactory::getLoginManger()
{
	return this->m_loginManager;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
	//to do
	return nullptr;
}

