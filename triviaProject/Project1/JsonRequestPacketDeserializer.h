#pragma once
#include "Responses.h"
#include <vector>
#include "json.hpp"
#include <iostream>
#include <bitset>



class JsonRequestPacketDeserializer {
public:
	static LoginResponse deserializeLoginRequest(const json& jsonData);
	static SignUpResponse deserializeSignUpRequest(const json& jsonData);
	static ErrorResponse deserializeErrorRequest(const json& jsonData);

private:
	static json getJson(std::vector<char unsigned> jsonResponseBits);
};