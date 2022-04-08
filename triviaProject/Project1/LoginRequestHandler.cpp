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
	requestResult.newHandler = new LoginRequestHandler();

	return requestResult;
}