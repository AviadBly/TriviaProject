#pragma once
#include "IRequestHandler.h"

class MenuRequestHandler : public IRequestHandler {
public:
	virtual bool isRequestRelevant(RequestInfo requestInfo) override;
	virtual RequestResult handleRequest(RequestInfo requestInfo) override;

};