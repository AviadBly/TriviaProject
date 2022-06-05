#include "JsonResponsePacketSerializer.h"


std::vector<BYTE> JsonResponsePacketSerializer::serializeLoginResponse(const LoginResponse& loginResponse)
{
	//init json
	json jsonResponse;
	
	jsonResponse[STATUS_TEXT] = loginResponse.status;

	std::vector<BYTE> jsonBits = convertJsonToBits(jsonResponse, BYTE(LOGIN_REQUEST_CODE));
	
	return jsonBits;
}

std::vector<BYTE> JsonResponsePacketSerializer::serializeSignupRequest(const SignUpResponse& signUpResponse)
{

	//init json
	json jsonResponse;

	jsonResponse[STATUS_TEXT] = signUpResponse.status;

	std::vector<BYTE> jsonBits = convertJsonToBits(jsonResponse, BYTE(SIGN_UP_REQUEST_CODE));

	return jsonBits;
}

std::vector<BYTE> JsonResponsePacketSerializer::serializeErrorResponse(const ErrorResponse& errorResponse)
{
	//init json
	json jsonResponse;
	jsonResponse[STATUS_TEXT] = errorResponse.status;
	jsonResponse[MESSAGE_TEXT] = errorResponse.message;
	
	std::vector<BYTE> jsonBits = convertJsonToBits(jsonResponse, BYTE(ERROR_RESPONSE_CODE));
	
	return jsonBits;
}

std::vector<BYTE> JsonResponsePacketSerializer::serializeLogoutResponse(const LogoutResponse& logoutResponse)
{
	//init json
	json jsonResponse;
	jsonResponse[STATUS_TEXT] = logoutResponse.status;
	
	std::vector<BYTE> jsonBits = convertJsonToBits(jsonResponse, BYTE(logoutResponse.status_ok));

	return jsonBits;
}

std::vector<BYTE> JsonResponsePacketSerializer::serializeCreateRoomResponse(const CreateRoomResponse& createRoomResponse)
{
	//init json
	json jsonResponse;
	jsonResponse[STATUS_TEXT] = createRoomResponse.status;

	std::vector<BYTE> jsonBits = convertJsonToBits(jsonResponse, BYTE(createRoomResponse.status_ok));

	return jsonBits;
}

std::vector<BYTE> JsonResponsePacketSerializer::serializeJoinRoomResponse(const JoinRoomResponse& joinRoomResponse)
{
	//init json
	json jsonResponse;
	jsonResponse[STATUS_TEXT] = joinRoomResponse.status;

	std::vector<BYTE> jsonBits = convertJsonToBits(jsonResponse, BYTE(joinRoomResponse.status_ok));

	return jsonBits;
}

std::vector<BYTE> JsonResponsePacketSerializer::serializeGetPlayersInRoomResponse(const GetPlayersInRoomResponse& getPlayersInRoomResponse)
{
	//init json
	json jsonResponse;
	jsonResponse[PLAYERS_TEXT] = getPlayersInRoomResponse.players;
	std::cout << jsonResponse;

	std::vector<BYTE> jsonBits = convertJsonToBits(jsonResponse, BYTE(1));

	return jsonBits;
}

//this may not be final
std::vector<BYTE> JsonResponsePacketSerializer::serializeGetRoomResponse(const GetRoomsResponse& getRoomsResponse)
{
	//init json
	json jsonResponse;
	std::string roomStr = "Room";
	jsonResponse[STATUS_TEXT] = getRoomsResponse.status;

	for (auto i = getRoomsResponse.rooms.begin(); i != getRoomsResponse.rooms.end(); i++) {
		
		RoomData data = i->getData();
		//add the roomData to the json format
		
		jsonResponse[ROOMS_TEXT] += {  {METADATA_TEXT, {
			   
			{ TIME_PER_QUESTION_TEXT, data.timePerQuestion },
			{ NUM_OF_QUESTIONS_IN_GAME_TEXT, data.numOfQuestionsInGame },
			{  NAME_TEXT,data.name},
			{ MAX_PLAYERS_TEXT, data.maxPlayers},
			{  IS_ACTIVE_TEXT, data.isActive},
			{ ID_TEXT, data.id }
			}  }, //add the players list in the room
			{ PLAYERS_TEXT, i->getAllUsersNames() }    };

		
		std::cout << jsonResponse;
					
		
		
	}
	
	
	std::cout << "final:\n" << jsonResponse << "\n";

	std::vector<BYTE> jsonBits = convertJsonToBits(jsonResponse, BYTE(1));

	return jsonBits;
}


std::vector<BYTE> JsonResponsePacketSerializer::serializeHighScoreResponse(const GetHighScoreResponse& getHighScoreResponse)
{
	//init json
	json jsonResponse;
	jsonResponse[STATUS_TEXT] = getHighScoreResponse.status;
	jsonResponse[HIGH_SCORE_PLAYERS] = getHighScoreResponse.statistics;
	std::cout << jsonResponse;

	std::vector<BYTE> jsonBits = convertJsonToBits(jsonResponse, BYTE(1));

	return jsonBits;
}

std::vector<BYTE> JsonResponsePacketSerializer::serializePersonalStatisticsResponse(const GetPersonalStatsResponse& getPersonalStatsResponse)
{
	//init json
	json jsonResponse;
	jsonResponse[STATUS_TEXT] = getPersonalStatsResponse.status;
	jsonResponse[PERSONAL_STATISTICS_TEXT] = getPersonalStatsResponse.statistics;
	std::cout << jsonResponse;

	std::vector<BYTE> jsonBits = convertJsonToBits(jsonResponse, BYTE(1));

	return jsonBits;
}



std::vector<BYTE> JsonResponsePacketSerializer::serializeGetRoomStateResponse(const GetRoomStateResponse& getRoomStateResponse) {

	//init json
	json jsonResponse;
	jsonResponse[STATUS_TEXT] = getRoomStateResponse.status;
	jsonResponse[GAME_BEGUN_TEXT] = getRoomStateResponse.hasGameBegun;
	jsonResponse[PLAYERS_TEXT] = getRoomStateResponse.players;
	jsonResponse[ANSWER_COUNT_TEXT] = getRoomStateResponse.questionCount;
	jsonResponse[ANSWER_TIMEOUT_TEXT] = getRoomStateResponse.answerTimeout;
	std::cout << jsonResponse;

	std::vector<BYTE> jsonBits = convertJsonToBits(jsonResponse, BYTE(1));

	return jsonBits;
}


std::vector<BYTE> JsonResponsePacketSerializer::serializeStartGameResponse(const StartRoomResponse& startRoomResponse) {
		
	//init json
	json jsonResponse;
	jsonResponse[STATUS_TEXT] = startRoomResponse.status;

	std::vector<BYTE> jsonBits = convertJsonToBits(jsonResponse, BYTE(1));

	return jsonBits;

}
std::vector<BYTE> JsonResponsePacketSerializer::serializeCloseRoomResponse(const CloseRoomResponse& closeRoomResponse) {

	//init json
	json jsonResponse;
	jsonResponse[STATUS_TEXT] = closeRoomResponse.status;

	std::vector<BYTE> jsonBits = convertJsonToBits(jsonResponse, BYTE(1));

	return jsonBits;

}

std::vector<BYTE> JsonResponsePacketSerializer::serializeLeaveRoomResponse(const LeaveRoomResponse& leaveRoomResponse) {

	//init json
	json jsonResponse;
	jsonResponse[STATUS_TEXT] = leaveRoomResponse.status;

	std::vector<BYTE> jsonBits = convertJsonToBits(jsonResponse, BYTE(1));

	return jsonBits;

}

std::vector<BYTE> JsonResponsePacketSerializer::serializeGetGameResultsResponse(const GetGameResultsResponse& getGameResultsResponse) {

	//init json
	json jsonResponse;
	jsonResponse[STATUS_TEXT] = getGameResultsResponse.status;


	for (auto i = getGameResultsResponse.results.begin(); i != getGameResultsResponse.results.end(); i++) {

		
		jsonResponse[RESULTS_TEXT] += { i->username, i->correctAnswerCount, i->wrongAnswerCount, i->averageAnswerCount};

		std::cout << jsonResponse;
	}
	

	std::vector<BYTE> jsonBits = convertJsonToBits(jsonResponse, BYTE(1));

	return jsonBits;

}

std::vector<BYTE> JsonResponsePacketSerializer::serializeSubmitAnswerResponse(const SubmitAnswerResponse& submitAnswerResponse) {

	//init json
	json jsonResponse;
	jsonResponse[STATUS_TEXT] = submitAnswerResponse.status;
	jsonResponse[CORRECT_ANSWER_ID_TEXT] = submitAnswerResponse.correctAnswerID;

	std::vector<BYTE> jsonBits = convertJsonToBits(jsonResponse, BYTE(1));

	return jsonBits;

}
std::vector<BYTE> JsonResponsePacketSerializer::serializeGetQuestionResponse(const GetQuestionResponse& getQuestionResponse) {

	//init json
	json jsonResponse;
	jsonResponse[STATUS_TEXT] = getQuestionResponse.status;
	jsonResponse[ANSWERS_TEXT] = getQuestionResponse.answers;
	jsonResponse[QUESTION_TEXT] = getQuestionResponse.question;

	std::vector<BYTE> jsonBits = convertJsonToBits(jsonResponse, BYTE(1));

	return jsonBits;

}
std::vector<BYTE> JsonResponsePacketSerializer::serializeLeaveGameResponse(const LeaveGameResponse& leaveGameResponse) {

	//init json
	json jsonResponse;
	jsonResponse[STATUS_TEXT] = leaveGameResponse.status;

	std::vector<BYTE> jsonBits = convertJsonToBits(jsonResponse, BYTE(1));

	return jsonBits;

}







std::vector<BYTE> JsonResponsePacketSerializer::intToBytes(int numInteger)
{
	vector<BYTE> arrayOfByte(4);
	for (int i = 0; i < 4; i++)
		arrayOfByte[3 - i] = (numInteger >> (i * 8));

	return arrayOfByte;
}

//return a vector of bits from the given jsonFormat message + 4 bits of the length of the message + the code
std::vector<BYTE> JsonResponsePacketSerializer::convertJsonToBits(const json& jsonFormat, BYTE code)
{


	//convert the json format to string
	std::string jsonString = jsonFormat.dump();
	std::vector<BYTE> jsonBits;

	//add the msg code
	jsonBits.push_back(code);

	//add the length of the data 
	unsigned int length = jsonString.length();
	std::vector<BYTE> tempLengthBytes = intToBytes(length);

	//runs 4 times because an integer is 32 bytes and each byte is 8, so 32/8=4
	for (unsigned int i = 0; i < 4; i++) {
		jsonBits.push_back(tempLengthBytes[i]);
	}

	std::cout << jsonString << "\n";
	//add the json string
	for (unsigned int i = 0; i < jsonString.length(); i++) {
		jsonBits.push_back(jsonString[i]);
	}

	return jsonBits;
}
