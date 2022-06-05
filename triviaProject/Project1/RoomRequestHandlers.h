#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"


class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRequestHandler {

public:

	RoomMemberRequestHandler(const LoggedUser& user, Room& room, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) const;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo);


	LoginManager& getLoginManger();
	RoomManager& getRoomManager();

protected:

	RequestResult leaveRoom();
	RequestResult getRoomState();

	unsigned int recentRoomId;
	LoggedUser m_user;
	Room& m_room;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

};


class RoomAdminRequestHandler : public RoomMemberRequestHandler {

public:

	RoomAdminRequestHandler(const LoggedUser& user, Room& room, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);
	virtual bool isRequestRelevant(const RequestInfo& requestInfo) const;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo);

private:

	RequestResult closeRoom();
	RequestResult startGame();

};