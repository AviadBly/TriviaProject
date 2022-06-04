#pragma once
#include <vector>
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoggedUser.h"
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
	//handlers
	LoginRequestHandler* createLoginRequestHandler();
	
	MenuRequestHandler* createMenuRequestHandler(LoggedUser newUser);

	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser loggedUser, Room room);
	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser loggedUser, Room room);
	GameRequestHandler* createGameRequestHandler(const vector<User>& users, const LoggedUser& user);

	//getters
	LoginManager& getLoginManger();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticsManager();
	GameManager& getGameManager();

private:
	//pointer to handler, so you dont have to create new ones all the time
	LoginRequestHandler* m_loginRequestHandler; //this is against the uml but its way better
	
	GameManager m_gameManager;
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;
	LoginManager m_loginManager;
	IDatabase* m_database;
};