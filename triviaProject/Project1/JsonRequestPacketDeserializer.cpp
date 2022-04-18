#include "JsonRequestPacketDeserializer.h"

//convert the bits vector to json
json JsonRequestPacketDeserializer::getJsonFromBits(std::vector<char unsigned> jsonBits)
{

	std::string jsonString = "";
	//create a json string, and replace all the \' with \" because \' is'nt registered well
	for (unsigned int i = 0; i < jsonBits.size(); i++) {
		if (jsonBits[i] == '\'') {
			jsonString += "\"";
		}
		else {
			jsonString += jsonBits[i];
		}
	}

	std::cout << "desirizlizer:" << jsonString << "\n";

	json jsonData = json::parse(jsonString);
	std::cout << jsonData << "\n";

	return jsonData;
}

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<char unsigned> jsonRequestBits)
{
	LoginRequest loginRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);

	loginRequest.username = jsonData.at("username");
	loginRequest.password = jsonData.at("password");
	
	return loginRequest;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(std::vector<char unsigned> jsonRequestBits)
{
	SignupRequest signUpRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);

	
	signUpRequest.username = jsonData.at("username");
	signUpRequest.password = jsonData.at("password");
	signUpRequest.email = jsonData.at("email");
	
	
	return signUpRequest;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<char unsigned> jsonRequestBits)
{
	CreateRoomRequest createRoomRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);
		
	createRoomRequest.answerTimeout = jsonData.at("answerTimeout");
	createRoomRequest.maxUsers = jsonData.at("maxUsers");
	createRoomRequest.questionCount = jsonData.at("questionCount");
	createRoomRequest.roomName = jsonData.at("roomName");
	
	return createRoomRequest;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<char unsigned> jsonRequestBits)
{
	JoinRoomRequest joinRoomRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);
	
	
	joinRoomRequest.roomId = jsonData.at("roomId");
	
	return joinRoomRequest;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(std::vector<char unsigned> jsonRequestBits)
{
	GetPlayersInRoomRequest getPlayersInRoomRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);


	getPlayersInRoomRequest.roomId = jsonData.at("roomId");

	return getPlayersInRoomRequest;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetRoomsRequest(std::vector<char unsigned> jsonRequestBits)
{
	GetPlayersInRoomRequest getPlayersInRoomRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);


	getPlayersInRoomRequest.roomId = jsonData.at("roomId");

	return getPlayersInRoomRequest;
}
//ErrorResponse JsonRequestPacketDeserializer::deserializeErrorResponse(std::vector<char unsigned> jsonResponseBits)
//{
//	ErrorResponse errorRequest;
//	//get json format from bits
//	json jsonData = getJsonFromBits(jsonResponseBits);
//
//	try {
//		errorRequest.message = jsonData.at("message");
//	}
//	catch (const std::exception& e) {
//		throw std::exception(e.what());
//	}
//	
//	return errorRequest;
//}
