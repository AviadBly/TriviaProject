#include "RequestInfo.h"
#include "LoginRequestHandler.h"
#include "Responses.h"

bool LoginRequestHandler::isRequestRelevant(RequestInfo requestInfo)
{
	return requestInfo.code == SIGN_RESPONSE_CODE || requestInfo.code == LOGIN_RESPONSE_CODE;
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult requestResult;
	requestResult.buffer = requestInfo.buffer;

	
	//adding IRequestHandler*
	requestResult.newHandler = this;
	
	return requestResult;
}

RequestResult LoginRequestHandler::login(RequestInfo requestInfo)
{
	RequestResult requestResult;
	requestResult.buffer = requestInfo.buffer;

	LoginResponse login = JsonRequestPacketDeserializer::deserializeLoginRequest(requestResult.buffer);

	this->m_loginManager.login(login.username, login.password);
	
	return requestResult;
}

RequestResult LoginRequestHandler::signUp(RequestInfo requestInfo)
{
	return RequestResult();
}