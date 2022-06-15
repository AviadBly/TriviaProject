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

#define ANSWER_ID_TEXT "AnswerId"

#define QUESTION_TEXT "Question"
#define ANSWER1_TEXT "Answer1"
#define ANSWER2_TEXT "Answer2"
#define ANSWER3_TEXT "Answer3"
#define CORRECT_TEXT "Correct"

using json = nlohmann::json;
using namespace std;

class JsonRequestPacketDeserializer {
public:
	//login
	static LoginRequest deserializeLoginRequest(const vector<BYTE>& jsonRequestBits);
	static SignupRequest deserializeSignUpRequest(const vector<BYTE>& jsonRequestBits);
	
	//rooms
	static CreateRoomRequest deserializeCreateRoomRequest(const vector<BYTE>& jsonRequestBits);
	static JoinRoomRequest deserializeJoinRoomRequest(const vector<BYTE>& jsonRequestBits);
	static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(const vector<BYTE>& jsonRequestBits);

	//game
	static SubmitAnswerRequest deserializeSubmitAnswerRequest(const vector<BYTE>& jsonRequestBits);

	static CreateQuestionRequest deserializeCreateQuestionRequest(const vector<BYTE>& jsonRequestBits);
	
private:
	static json getJsonFromBits(const std::vector<BYTE>& constJsonBits);
};