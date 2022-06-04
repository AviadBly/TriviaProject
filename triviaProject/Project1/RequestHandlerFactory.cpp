#include "RequestHandlerFactory.h"


RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_loginManager(database), m_statisticsManager(database) ,m_gameManager(database) {

	this->m_database = database;
	this->m_loginRequestHandler = new LoginRequestHandler(m_loginManager, *this);
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	delete this->m_database;
	delete this->m_loginRequestHandler;
}


LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return (this->m_loginRequestHandler);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(const LoggedUser& newUser)
{
	return new MenuRequestHandler(*this, newUser);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(const LoggedUser& newUser, const Room& room)
{
	return new RoomMemberRequestHandler(room, newUser, m_roomManager, *this);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(const LoggedUser& newUser, const Room& room)
{
	return new RoomAdminRequestHandler(room, newUser, m_roomManager, *this);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(const vector<User>& users, const LoggedUser& user, unsigned int timePerQuestion)
{
	return new GameRequestHandler(users, user, timePerQuestion, m_gameManager, *this);
}


//getters
LoginManager& RequestHandlerFactory::getLoginManger()
{
	return this->m_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManager()
{
	return this->m_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager()
{
	return this->m_statisticsManager;
}

GameManager& RequestHandlerFactory::getGameManager()
{
	return this->m_gameManager;
}