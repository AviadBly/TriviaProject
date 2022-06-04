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



MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser loggeduser)
{
	return new MenuRequestHandler(*this, loggeduser);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(LoggedUser loggedUser, Room room)
{
	return new RoomMemberRequestHandler(room, loggedUser, m_roomManager, *this);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(LoggedUser loggedUser, Room room)
{
	return new RoomAdminRequestHandler(room, loggedUser, m_roomManager, *this);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(const vector<User>& users, const LoggedUser& user)
{
	return new GameRequestHandler(users, user, this->m_gameManager, *this);
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