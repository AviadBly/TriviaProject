#pragma once
#include "Responses.h"
#include <vector>
#include "json.hpp"

class JsonResponePacketSerializer {
	static std::vector<int> serializeLoginResponse(const LoginResponse& loginResponse);
};