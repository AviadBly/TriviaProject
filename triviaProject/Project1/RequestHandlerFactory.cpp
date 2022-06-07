#include "RequestHandlerFactory.h"


RequestHandlerFactory::RequestHandlerFactory(IDatabase* database) : m_loginManager(database), m_statisticsManager(database) {

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

LoginManager& RequestHandlerFactory::getLoginManger()
{
	return this->m_loginManager;
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

