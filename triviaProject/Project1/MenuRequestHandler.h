#pragma once
#include "IRequestHandler.h"
#include "Requests.h"
#include "Users.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "RequestHandlerFactory.h"
#include "Responses.h"
#include "JsonRequestPacketDeserializer.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler {
public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory, LoggedUser newUser);

	virtual bool isRequestRelevant(const RequestInfo& requestInfo) const;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo);

private:

	RequestResult createRoom(const RequestInfo& requestInfo);
	
	RequestResult getRooms();
	RequestResult getPlayersInRoom(const RequestInfo& requestInfo);
	RequestResult joinRoom(const RequestInfo& requestInfo);
	
	RequestResult getHighScore() const;
	RequestResult getPersonalStatistics() const;

	RequestResult logOut();

	RequestResult CreateQuestion(const RequestInfo& requestInfo);

	LoggedUser m_user;
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;
	RequestHandlerFactory& m_handlerFactory;

};