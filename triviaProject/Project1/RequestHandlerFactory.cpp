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
	return new RoomMemberRequestHandler(newUser, room , m_roomManager, *this);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(const LoggedUser& newUser, const Room& room)
{
	return new RoomAdminRequestHandler(newUser, room, m_roomManager, *this);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(const Room& room, const LoggedUser& user, bool isAdmin)
{
	
	if (isAdmin) {
		//create new room
		RoomData metaData = room.getData();
		return new GameRequestHandler(m_gameManager.createGame(room.getAllUsers(), metaData.timePerQuestion, metaData.id, metaData.numOfQuestionsInGame), //this is the new game
			user, m_gameManager, *this);
	}
	//join room
	return new GameRequestHandler(m_gameManager.joinGame(room.getData().id), user, m_gameManager, *this);
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