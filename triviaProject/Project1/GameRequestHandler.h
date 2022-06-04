#pragma once
#pragma once
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"
#include "Game.h"
#include <time.h> 


class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler {

public:

	GameRequestHandler(const vector<User>& users, const LoggedUser& user, GameManager& gameManager, RequestHandlerFactory& handleFactory);


	virtual bool isRequestRelevant(RequestInfo requestInfo) const;
	virtual RequestResult handleRequest(RequestInfo requestInfo);

	
private:

	RequestResult leaveGame();
	RequestResult getQuestion();
	RequestResult submitAnswer(RequestInfo requestInfo);
	RequestResult getGameResults();

	time_t sendingTime;
	Game m_game;
	LoggedUser m_user;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;

};