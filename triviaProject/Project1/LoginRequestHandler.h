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
	

	virtual bool isRequestRelevant(const RequestInfo& requestInfo) const;
	virtual RequestResult handleRequest(const RequestInfo& requestInfo);

private:
	RequestResult login(const RequestInfo& requestInfo);
	RequestResult signUp(const RequestInfo& requestInfo);

	void loadErrorMsg(RequestResult& requestResult, std::string msg);

	static bool isUsernameValid(const string& username);
	static bool isPasswordValid(const string& password);

	LoginManager& m_loginManager;
	RequestHandlerFactory& m_handleFactory;
};
