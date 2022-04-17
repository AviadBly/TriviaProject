#include "RequestHandlerFactory.h"


<<<<<<< HEAD
RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) {
	this->m_database = database;
	this->m_loginManager = LoginManager(database);
=======
RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_loginManager(database) {
	this->m_database = database;
	this->m_loginRequestHandler = new LoginRequestHandler(m_loginManager, *this);
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
<<<<<<< HEAD
	//not sure if its correct
	LoginRequestHandler loginRequestHandler(getLoginManger(), *this);

	return &loginRequestHandler;
=======
	return (this->m_loginRequestHandler);
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
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

