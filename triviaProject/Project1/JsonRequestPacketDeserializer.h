#pragma once
#include "Responses.h"
#include <vector>
#include "json.hpp"
#include <iostream>
#include <bitset>



class JsonRequestPacketDeserializer {
public:
	static LoginResponse deserializeLoginRequest(std::vector<char unsigned> jsonResponseBits);
	static SignUpResponse deserializeSignUpRequest(std::vector<char unsigned> jsonResponseBits);
	static ErrorResponse deserializeErrorRequest(std::vector<char unsigned> jsonResponseBits);

private:
	static json& getJson(std::vector<char unsigned> jsonResponseBits);
};