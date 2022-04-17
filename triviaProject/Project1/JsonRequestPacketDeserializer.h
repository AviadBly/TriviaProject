#pragma once
#include <vector>
#include <iostream>
#include <bitset>
#include "json.hpp"
#include "Login_SignUp_Requests.h"
#include "Responses.h"

using json = nlohmann::json;

class JsonRequestPacketDeserializer {
public:
	static LoginRequest deserializeLoginResponse(std::vector<char unsigned> jsonResponseBits);
	static SignupRequest deserializeSignUpResponse(std::vector<char unsigned> jsonResponseBits);
	static ErrorResponse deserializeErrorResponse(std::vector<char unsigned> jsonResponseBits);

private:
	static json getJsonFromBits(std::vector<char unsigned> jsonResponseBits);
};