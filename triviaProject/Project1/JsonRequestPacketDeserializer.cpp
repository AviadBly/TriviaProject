#include "JsonRequestPacketDeserializer.h"



LoginResponse JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<char unsigned> jsonResponseBits)
{
	LoginResponse loginRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonResponseBits);

	loginRequest.status = jsonData.at("status");
	loginRequest.username = jsonData.at("username");
	loginRequest.password = jsonData.at("password");

	return loginRequest;
}

SignUpResponse JsonRequestPacketDeserializer::deserializeSignUpRequest(std::vector<char unsigned> jsonResponseBits)
{
	SignUpResponse signUpRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonResponseBits);

	signUpRequest.status = jsonData.at("status");
	signUpRequest.username = jsonData.at("username");
	signUpRequest.password = jsonData.at("password");
	signUpRequest.email = jsonData.at("email");

	return signUpRequest;
}

ErrorResponse JsonRequestPacketDeserializer::deserializeErrorRequest(std::vector<char unsigned> jsonResponseBits)
{
	ErrorResponse errorRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonResponseBits);

	errorRequest.status = jsonData.at("status");
	errorRequest.message = jsonData.at("message");

	return errorRequest;
}

//convert the bits vector to json
json JsonRequestPacketDeserializer::getJsonFromBits(std::vector<char unsigned> jsonResponseBits)
{
	std::string jsonString = "";
	//create a json string, and replace all the \' with \"
	for (int i = 0; i < jsonResponseBits.size(); i++) {
		if (jsonResponseBits[i] == '\'') {
			jsonString += "\"";
		}
		else {
			jsonString += jsonResponseBits[i];
		}
		

	}
	
	std::cout << "desirizlizer:" << jsonString << "\n";
	
	json jsonData = json::parse(jsonString);
	std::cout << jsonData << "\n";

	return jsonData;
}