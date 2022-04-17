#include "RequestHandlerFactory.h"


<<<<<<< HEAD
RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_loginManager(database) {
	this->m_database = database;
	this->m_loginRequestHandler = new LoginRequestHandler(m_loginManager, *this);
=======
<<<<<<< HEAD
RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) {
	this->m_database = database;
	this->m_loginManager = LoginManager(database);
=======
RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_loginManager(database) {
	this->m_database = database;
	this->m_loginRequestHandler = new LoginRequestHandler(m_loginManager, *this);
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
<<<<<<< HEAD
	return (this->m_loginRequestHandler);
=======
<<<<<<< HEAD
	//not sure if its correct
	LoginRequestHandler loginRequestHandler(getLoginManger(), *this);

	return &loginRequestHandler;
=======
	return (this->m_loginRequestHandler);
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71
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

