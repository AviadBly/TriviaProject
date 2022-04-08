#pragma once
#include "Responses.h"
#include <vector>
#include "json.hpp"
#include <iostream>
#include <bitset>

using json = nlohmann::json;

class JsonResponePacketSerializer {
public:
	static std::vector<unsigned char> serializeLoginResponse(const LoginResponse& loginResponse);
	static std::vector<unsigned char> serializeSignUpResponse(const SignUpResponse& loginResponse);
	static std::vector<unsigned char> serializeErrorResponse(const ErrorResponse& signUpResponse);

private:
	static std::vector<unsigned char> convertJsonToBits(const json& jsonFormat);
};