#pragma once
#include <vector>
#include "IDatabase.h"
#include "LoginManager.h"
#include "LoggedUser.h"
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "StatisticsManager.h"
#include "RoomManager.h"
#include "RoomAdminRequestHandler.h"
#include "RoomMemberRequestHandler.h"

class LoginRequestHandler;
class MenuRequestHandler;

class RequestHandlerFactory {

public:
	RequestHandlerFactory(IDatabase* database);
	~RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	
	MenuRequestHandler* createMenuRequestHandler(LoggedUser newUser);

	RoomAdminRequestHandler* createRoomAdminRequestHandler(LoggedUser loggedUser, Room room);
	RoomMemberRequestHandler* createRoomMemberRequestHandler(LoggedUser loggedUser, Room room);

	//getters
	LoginManager& getLoginManger();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticsManager();

private:
	//pointer to handler, so you dont have to create new ones all the time
	LoginRequestHandler* m_loginRequestHandler; //this is against the uml but its way better
	
	RoomManager m_roomManager;
	StatisticsManager m_statisticsManager;
	LoginManager m_loginManager;
	IDatabase* m_database;
};