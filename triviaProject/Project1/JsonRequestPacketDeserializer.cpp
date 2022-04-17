#include "JsonRequestPacketDeserializer.h"

//convert the bits vector to json
json JsonRequestPacketDeserializer::getJsonFromBits(std::vector<char unsigned> jsonBits)
{
<<<<<<< HEAD

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
=======

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

<<<<<<< HEAD
LoginRequest JsonRequestPacketDeserializer::deserializeLoginResponse(std::vector<char unsigned> jsonResponseBits)
=======
	return jsonData;
}

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<char unsigned> jsonRequestBits)
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71
{
	LoginRequest loginRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);
<<<<<<< HEAD

=======

<<<<<<< HEAD
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
=======
>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71
	loginRequest.username = jsonData.at("username");
	loginRequest.password = jsonData.at("password");
	
	return loginRequest;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(std::vector<char unsigned> jsonRequestBits)
<<<<<<< HEAD
=======
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71
{
	SignupRequest signUpRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);
<<<<<<< HEAD

=======

<<<<<<< HEAD
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
=======
>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71
	
	signUpRequest.username = jsonData.at("username");
	signUpRequest.password = jsonData.at("password");
	signUpRequest.email = jsonData.at("email");
	
	
	return signUpRequest;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<char unsigned> jsonRequestBits)
<<<<<<< HEAD
{
	CreateRoomRequest createRoomRequest;
	//get json format from bits
=======
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
{
	CreateRoomRequest createRoomRequest;
	//get json format from bits
<<<<<<< HEAD
	json jsonData = getJsonFromBits(jsonResponseBits);

	try {
		errorRequest.message = jsonData.at("message");
	}
	catch (const std::exception& e) {
		throw std::exception(e.what());
	}
	
	return errorRequest;
=======
>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71
	json jsonData = getJsonFromBits(jsonRequestBits);
		
	createRoomRequest.answerTimeout = jsonData.at("answerTimeout");
	createRoomRequest.maxUsers = jsonData.at("maxUsers");
	createRoomRequest.questionCount = jsonData.at("questionCount");
	createRoomRequest.roomName = jsonData.at("roomName");
	
	return createRoomRequest;
<<<<<<< HEAD
=======
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<char unsigned> jsonRequestBits)
{
<<<<<<< HEAD
	JoinRoomRequest joinRoomRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);
=======
<<<<<<< HEAD
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
=======
	JoinRoomRequest joinRoomRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71
	
	
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
