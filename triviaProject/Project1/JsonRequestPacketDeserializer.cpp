#include "JsonRequestPacketDeserializer.h"

//convert the bits vector to json
json JsonRequestPacketDeserializer::getJsonFromBits(const vector<BYTE>& constJsonBits)
{

	string jsonString = "";
	vector<BYTE> jsonBits = constJsonBits;
	//create a json string, and replace all the \' with \"       because \' is'nt registered well
	for (unsigned int i = 0; i < jsonBits.size(); i++) {
		if (jsonBits[i] == '\'') {
			jsonString += "\"";
		}
		else {
			jsonString += jsonBits[i];
		}
	}

	cout << "desirizlizer:" << jsonString << "\n";

	json jsonData = json::parse(jsonString);
	cout << jsonData << "\n";

	return jsonData;
}

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(const vector<BYTE>& jsonRequestBits)
{
	LoginRequest loginRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);

	loginRequest.username = jsonData.at(USERNAME_TEXT);
	loginRequest.password = jsonData.at(PASSWORD_TEXT);
	
	return loginRequest;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(const vector<BYTE>& jsonRequestBits)
{
	SignupRequest signUpRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);

	cout << jsonData << "\n";
	signUpRequest.username = jsonData.at(USERNAME_TEXT);
	signUpRequest.password = jsonData.at(PASSWORD_TEXT);
	signUpRequest.email = jsonData.at(EMAIL_TEXT);
	
	
	return signUpRequest;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(const vector<BYTE>& jsonRequestBits)
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

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(const vector<BYTE>& jsonRequestBits)
{
	JoinRoomRequest joinRoomRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);
	
	
	joinRoomRequest.roomId = jsonData.at(ROOM_ID_TEXT);
	
	return joinRoomRequest;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(const vector<BYTE>& jsonRequestBits)
{
	GetPlayersInRoomRequest getPlayersInRoomRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);


	getPlayersInRoomRequest.roomId = jsonData.at(ROOM_ID_TEXT);

	return getPlayersInRoomRequest;
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(const vector<BYTE>& jsonRequestBits)
{
	SubmitAnswerRequest submitAnswerRequest;
	//get json format from bits
	json jsonData = getJsonFromBits(jsonRequestBits);


	submitAnswerRequest.answerId = jsonData.at(ANSWER_ID_TEXT);

	return submitAnswerRequest;
}


//ErrorResponse JsonRequestPacketDeserializer::deserializeErrorResponse(vector<BYTE> jsonResponseBits)
//{
//	ErrorResponse errorRequest;
//	//get json format from bits
//	json jsonData = getJsonFromBits(jsonResponseBits);
//
//	try {
//		errorRequest.message = jsonData.at("message");
//	}
//	catch (const exception& e) {
//		throw exception(e.what());
//	}
//	
//	return errorRequest;
//}
