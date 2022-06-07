#pragma once
#include "IRequestHandler.h"
#include "RoomManager.h"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"


class RequestHandlerFactory;

class RoomMemberRequestHandler : public IRequestHandler {

public:

	RoomMemberRequestHandler(Room room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);
	virtual bool isRequestRelevant(RequestInfo requestInfo) const;
	virtual RequestResult handleRequest(RequestInfo requestInfo);


	LoginManager& getLoginManger();
	RoomManager& getRoomManager();

protected:

	RequestResult leaveRoom(RequestInfo requestInfo);
	RequestResult getRoomState(RequestInfo requestInfo);

	Room m_room;
	LoggedUser m_user;
	RoomManager& m_roomManager;
	RequestHandlerFactory& m_handlerFactory;

};


class RoomAdminRequestHandler : public RoomMemberRequestHandler {

public:

	RoomAdminRequestHandler(Room room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory);
	virtual bool isRequestRelevant(RequestInfo requestInfo) const;
	virtual RequestResult handleRequest(RequestInfo requestInfo);

private:

	RequestResult closeRoom(RequestInfo requestInfo);
	RequestResult startGame(RequestInfo requestInfo);

};