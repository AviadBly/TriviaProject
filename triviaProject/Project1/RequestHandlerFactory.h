#pragma once
#include <vector>
#include "IDatabase.h"
#include "LoginManager.h"
#include "Users.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"
#include "RoomManager.h"
#include "GameManager.h"
#include "RoomRequestHandlers.h"
#include "GameRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;
class RoomMemberRequestHandler;
class RoomAdminRequestHandler;
class GameRequestHandler;

class RequestHandlerFactory {

public:
	RequestHandlerFactory(IDatabase* database);
	~RequestHandlerFactory();

	//create handlers
	LoginRequestHandler* createLoginRequestHandler();

	MenuRequestHandler* createMenuRequestHandler(const LoggedUser& newUser);

	RoomMemberRequestHandler* createRoomMemberRequestHandler(const LoggedUser& newUser, const Room& room);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(const LoggedUser& newUser, const Room& room);

	GameRequestHandler* createGameRequestHandler(const Room& room, const LoggedUser& user, bool isAdmin);

	//getters
	LoginManager& getLoginManger();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticsManager();
	GameManager& getGameManager();

private:
	//pointer to handler, so you dont have to create new ones all the time
	LoginRequestHandler* m_loginRequestHandler; 
	
	GameManager m_gameManager;
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;
	LoginManager m_loginManager;
	IDatabase* m_database;
};