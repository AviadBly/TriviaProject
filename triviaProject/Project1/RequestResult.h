#pragma once
#include <vector>
#include "IRequestHandler.h"

class IRequestHandler;

struct RequestResult {
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler;
};