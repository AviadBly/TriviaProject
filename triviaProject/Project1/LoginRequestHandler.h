#pragma once
#include "JsonRequestPacketDeserializer.h"
#include "JsonResponsePacketSerializer.h"
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"

class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler {

public:
	
	LoginRequestHandler(LoginManager& loginManager, RequestHandlerFactory& handleFactory);
<<<<<<< HEAD
=======
	//LoginRequestHandler(LoginManager& loginManager);
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f

	virtual bool isRequestRelevant(RequestInfo requestInfo);
	virtual RequestResult handleRequest(RequestInfo requestInfo);

private:
	RequestResult login(RequestInfo requestInfo);
	RequestResult signUp(RequestInfo requestInfo);

	void loadErrorMsg(RequestResult& requestResult, std::string msg);

	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handleFactory;
};
