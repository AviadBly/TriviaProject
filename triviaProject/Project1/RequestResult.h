#pragma once
#include <vector>
#include "Responses.h"
#include "IRequestHandler.h"

class IRequestHandler;

struct RequestResult {
	RequestResult() {
		newHandler = nullptr;
	}
	std::vector<BYTE> buffer;
	IRequestHandler* newHandler;
};