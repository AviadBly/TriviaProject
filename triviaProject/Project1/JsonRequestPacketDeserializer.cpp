#include "JsonRequestPacketDeserializer.h"



LoginRequest JsonRequestPacketDeserializer::deserializeLoginResponse(std::vector<char unsigned> jsonResponseBits)
{
	LoginRequest loginRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonResponseBits);

	try {
		loginRequest.username = jsonData.at("username");
		loginRequest.password = jsonData.at("password");
	}
	catch (const std::exception& e) {
		throw std::exception(e.what());
	}
	

	return loginRequest;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignUpResponse(std::vector<char unsigned> jsonResponseBits)
{
	SignupRequest signUpRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonResponseBits);

	try {
		signUpRequest.username = jsonData.at("username");
		signUpRequest.password = jsonData.at("password");
		signUpRequest.email = jsonData.at("email");
	}
	catch (const std::exception& e) {
		throw std::exception(e.what());
	}
	

	return signUpRequest;
}

ErrorResponse JsonRequestPacketDeserializer::deserializeErrorResponse(std::vector<char unsigned> jsonResponseBits)
{
	ErrorResponse errorRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonResponseBits);

	try {
		errorRequest.message = jsonData.at("message");
	}
	catch (const std::exception& e) {
		throw std::exception(e.what());
	}
	
	return errorRequest;
}

//convert the bits vector to json
json JsonRequestPacketDeserializer::getJsonFromBits(std::vector<char unsigned> jsonResponseBits)
{
	std::string jsonString = "";
	//create a json string, and replace all the \' with \"
	for (unsigned int i = 0; i < jsonResponseBits.size(); i++) {
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