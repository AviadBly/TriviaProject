#pragma once
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"
#include "Game.h"
#include <time.h> 
#include "ServerException.h"
#include <chrono>
#include <thread>

#define ERROR_MSG_USER_DELAY "No Response Was Given from user in the specified time"

class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler {

public:

	GameRequestHandler(const Room room, const LoggedUser user, bool isAdmin, GameManager& gameManager, RequestHandlerFactory& handleFactory);


	virtual bool isRequestRelevant(const RequestInfo& requestInfo) const;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo);

	
private:

	RequestResult leaveGame();
	RequestResult getQuestion();
	
	RequestResult submitAnswer(RequestInfo requestInfo);
	RequestResult getGameResults();

	time_t sendingTime;
		

	LoggedUser m_user;
	Game m_game;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;

};