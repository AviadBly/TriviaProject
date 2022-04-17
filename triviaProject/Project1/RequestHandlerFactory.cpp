#include "RequestHandlerFactory.h"


RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_loginManager(database) {
	this->m_database = database;
	this->m_loginRequestHandler = new LoginRequestHandler(m_loginManager, *this);
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return (this->m_loginRequestHandler);
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

