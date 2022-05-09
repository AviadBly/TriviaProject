#pragma once
#include "RequestInfo.h"
#include "RequestResult.h"


class IRequestHandler {
public:
	virtual bool isRequestRelevant(RequestInfo requestInfo) const = 0;
	virtual RequestResult handleRequest(RequestInfo requestInfo) = 0;
};
