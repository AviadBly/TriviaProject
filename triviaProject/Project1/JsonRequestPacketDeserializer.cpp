#include "JsonRequestPacketDeserializer.h"

using namespace nlohmann;

LoginResponse JsonRequestPacketDeserializer::deserializeLoginRequest(const json& jsonData)
{
	LoginResponse loginRequest;
	

	loginRequest.status = jsonData.at("status");
	loginRequest.username = jsonData.at("username");
	loginRequest.password = jsonData.at("password");

	return loginRequest;
}

SignUpResponse JsonRequestPacketDeserializer::deserializeSignUpRequest(const json& jsonData)
{
	SignUpResponse signUpRequest;


	signUpRequest.status = jsonData.at("status");
	signUpRequest.username = jsonData.at("username");
	signUpRequest.password = jsonData.at("password");
	signUpRequest.email = jsonData.at("email");

	return signUpRequest;
}

ErrorResponse JsonRequestPacketDeserializer::deserializeErrorRequest(const json& jsonData)
{
	ErrorResponse errorRequest;

	errorRequest.status = jsonData.at("status");
	
	return errorRequest;
}

//convert the bits vector to json
json JsonRequestPacketDeserializer::getJson(std::vector<char unsigned> jsonResponseBits)
{
	std::string jsonString = "";
	for (int i = 0; i < jsonResponseBits.size(); i++) {
		jsonString += jsonResponseBits[i];
	}
	std::cout << "desirizlizer:" << jsonString << "\n";
	
	json jsonData = json::parse(jsonString);
	std::cout << jsonData << "\n";

	return jsonData;
}