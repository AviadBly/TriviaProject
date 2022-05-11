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
	

	virtual bool isRequestRelevant(RequestInfo requestInfo) const;
	virtual RequestResult handleRequest(RequestInfo requestInfo);

private:
	RequestResult login(RequestInfo requestInfo);
	RequestResult signUp(RequestInfo requestInfo);

	void loadErrorMsg(RequestResult& requestResult, std::string msg);

	static bool isUsernameValid(string& username);
	static bool isPasswordValid(string& password);

	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handleFactory;
};
