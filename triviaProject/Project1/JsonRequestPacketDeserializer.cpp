#include "JsonRequestPacketDeserializer.h"

//convert the bits vector to json
json JsonRequestPacketDeserializer::getJsonFromBits(std::vector<BYTE> jsonBits)
{

	std::string jsonString = "";
	//create a json string, and replace all the \' with \"       because \' is'nt registered well
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

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<BYTE> jsonRequestBits)
{
	LoginRequest loginRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);

	loginRequest.username = jsonData.at(USERNAME_TEXT);
	loginRequest.password = jsonData.at(PASSWORD_TEXT);
	
	return loginRequest;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(std::vector<BYTE> jsonRequestBits)
{
	SignupRequest signUpRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);

	std::cout << jsonData << "\n";
	signUpRequest.username = jsonData.at(USERNAME_TEXT);
	signUpRequest.password = jsonData.at(PASSWORD_TEXT);
	signUpRequest.email = jsonData.at(EMAIL_TEXT);
	
	
	return signUpRequest;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector<BYTE> jsonRequestBits)
{
	CreateRoomRequest createRoomRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);
		
	createRoomRequest.answerTimeout = jsonData.at(ANSWER_TIMEOUT_TEXT);
	createRoomRequest.maxUsers = jsonData.at(MAX_USERS_TEXT);
	createRoomRequest.questionCount = jsonData.at(QUESTION_COUNT_TEXT);
	createRoomRequest.roomName = jsonData.at(ROOM_NAME_TEXT);
	
	return createRoomRequest;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector<BYTE> jsonRequestBits)
{
	JoinRoomRequest joinRoomRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);
	
	
	joinRoomRequest.roomId = jsonData.at(ROOM_ID_TEXT);
	
	return joinRoomRequest;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(std::vector<BYTE> jsonRequestBits)
{
	GetPlayersInRoomRequest getPlayersInRoomRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);


	getPlayersInRoomRequest.roomId = jsonData.at(ROOM_ID_TEXT);

	return getPlayersInRoomRequest;
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(std::vector<BYTE> jsonRequestBits)
{
	SubmitAnswerRequest submitAnswerRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);


	submitAnswerRequest.answerId = jsonData.at(ROOM_ID_TEXT);

	return submitAnswerRequest;
}


//ErrorResponse JsonRequestPacketDeserializer::deserializeErrorResponse(std::vector<BYTE> jsonResponseBits)
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
