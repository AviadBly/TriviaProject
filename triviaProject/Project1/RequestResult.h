#pragma once
#include <vector>
#include "IRequestHandler.h"

struct RequestResult {
	std::vector<unsigned char> buffer;
	IRequestHandler* newHandler;
};