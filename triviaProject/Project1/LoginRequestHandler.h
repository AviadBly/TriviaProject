#pragma once
#include "JsonRequestPacketDeserializer.h"
#include "IRequestHandler.h"
#include "LoginManager.h"
#include "RequestHandlerFactory.h"
#include "MenuRequestHandler.h"

class LoginRequestHandler : public IRequestHandler {

public:
	LoginRequestHandler();
	virtual bool isRequestRelevant(RequestInfo requestInfo);
	virtual RequestResult handleRequest(RequestInfo requestInfo);

private:
	RequestResult login(RequestInfo requestInfo);
	RequestResult signUp(RequestInfo requestInfo);

	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handleFactory;
};
