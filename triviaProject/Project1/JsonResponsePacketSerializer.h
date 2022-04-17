#pragma once
#include "Login_SignUp_Requests.h"
#include "Responses.h"
#include <vector>
#include "json.hpp"
#include <iostream>
#include <bitset>

using json = nlohmann::json;

class JsonResponsePacketSerializer {
public:
	static std::vector<unsigned char> serializeLoginResponse(const LoginResponse& LoginRequest);
	static std::vector<unsigned char> serializeSignupRequest(const SignUpResponse& LoginRequest);
	static std::vector<unsigned char> serializeErrorResponse(const ErrorResponse& SignupRequest);

private:
	static std::vector<unsigned char> convertJsonToBits(const json& jsonFormat, unsigned char code);
};