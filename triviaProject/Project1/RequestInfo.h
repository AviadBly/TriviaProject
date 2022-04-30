#pragma once
#include <ctime>
#include <vector>

struct RequestInfo {
	unsigned int code;
	time_t receivalTime;
	std::vector<unsigned char> buffer;
};