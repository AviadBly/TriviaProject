#pragma once
#include <vector>
#include <iostream>
#include <bitset>
#include "json.hpp"
#include "Requests.h"
#include "Responses.h"

#define USERNAME_TEXT "Username"
#define PASSWORD_TEXT "Password"
#define EMAIL_TEXT "Email"

#define ANSWER_TIMEOUT_TEXT "AnswerTimeout"
#define MAX_USERS_TEXT "MaxUsers"
#define QUESTION_COUNT_TEXT "QuestionCount"
#define ROOM_NAME_TEXT "RoomName"

#define ROOM_ID_TEXT "RoomId"
using json = nlohmann::json;

class JsonRequestPacketDeserializer {
public:
	//login
	static LoginRequest deserializeLoginRequest(std::vector<BYTE> jsonRequestBits);
	static SignupRequest deserializeSignUpRequest(std::vector<BYTE> jsonRequestBits);
	//error
	//static ErrorRequest deserializeErrorRequest(std::vector<BYTE> jsonRequestBits);
	
	//rooms
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<BYTE> jsonRequestBits);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<BYTE> jsonRequestBits);
	static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(std::vector<BYTE> jsonRequestBits);
	
private:
	static json getJsonFromBits(std::vector<BYTE> jsonRequestBits);
};