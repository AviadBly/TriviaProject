#pragma once
#include "IRequestHandler.h"

class LoginRequestHandler : public IRequestHandler {

public:
	virtual bool isRequestRelevant(RequestInfo requestInfo);
	virtual RequestResult handleRequest(RequestInfo requestInfo);

private:

};
