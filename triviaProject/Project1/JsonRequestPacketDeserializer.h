#pragma once
#include <vector>
#include <iostream>
#include <bitset>
#include "json.hpp"
#include "Responses.h"


using json = nlohmann::json;

class JsonRequestPacketDeserializer {
public:
	static LoginResponse deserializeLoginRequest(std::vector<char unsigned> jsonResponseBits);
	static SignUpResponse deserializeSignUpRequest(std::vector<char unsigned> jsonResponseBits);
	static ErrorResponse deserializeErrorRequest(std::vector<char unsigned> jsonResponseBits);

private:
	static json getJsonFromBits(std::vector<char unsigned> jsonResponseBits);
};