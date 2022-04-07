#pragma once
#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler {
	virtual bool isRequestRelevant(RequestInfo requestInfo);
	virtual RequestResult handleRequest(RequestInfo requestInfo);
};
