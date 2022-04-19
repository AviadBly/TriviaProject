#pragma once
#include "IRequestHandler.h"
#include "Requests.h"
#include "LoggedUser.h"
#include "RoomManager.h"
#include "StatisticsManager.h"
#include "RequestHandlerFactory.h"
#include "Responses.h"
#include "JsonRequestPacketDeserializer.h"

class RequestHandlerFactory;

class MenuRequestHandler : public IRequestHandler {
public:
	MenuRequestHandler(RequestHandlerFactory& handlerFactory);

	virtual bool isRequestRelevant(RequestInfo requestInfo) override;
	virtual RequestResult handleRequest(RequestInfo requestInfo) override;

private:

	RequestResult logOut(RequestInfo requestInfo);
	RequestResult getRooms(RequestInfo requestInfo);
	RequestResult getPlayersInRoom(RequestInfo requestInfo);
	RequestResult joinRoom(RequestInfo requestInfo);
	RequestResult createRoom(RequestInfo requestInfo);
	RequestResult getHighScore(RequestInfo requestInfo);


	LoggedUser m_user;
	RoomManager& m_roomManager;
	StatisticsManager& m_statisticsManager;
	RequestHandlerFactory& m_handlerFactory;

};