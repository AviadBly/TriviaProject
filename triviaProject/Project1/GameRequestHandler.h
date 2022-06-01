#pragma once
#pragma once
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"
#include "Game.h"


class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler {

public:

	GameRequestHandler(Game game, LoggedUser user, GameManager& gameManager, RequestHandlerFactory& handleFactory);


	virtual bool isRequestRelevant(RequestInfo requestInfo) const;
	virtual RequestResult handleRequest(RequestInfo requestInfo);

	


private:

	RequestResult leaveGame();

	RequestResult getQuestion();

	RequestResult submitAnswer(RequestInfo requestInfo);

	RequestResult getGameResults();



	Game m_game;
	LoggedUser m_user;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;

};