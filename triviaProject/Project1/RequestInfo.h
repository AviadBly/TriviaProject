#pragma once
#include <ctime>
#include <vector>
#include "Responses.h"

struct RequestInfo {
	BYTE code;
	time_t receivalTime;
	std::vector<unsigned char> buffer;
};