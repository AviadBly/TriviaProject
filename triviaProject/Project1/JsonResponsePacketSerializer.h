#pragma once
#include "Requests.h"
#include "Responses.h"
#include <vector>
#include "json.hpp"
#include <iostream>
#include <bitset>

#define STATUS_TEXT "Status"
#define MESSAGE_TEXT "Message"
#define PLAYERS_TEXT "Players"

#define IS_ACTIVE_TEXT "IsActive"

#define MAX_PLAYERS_TEXT "MaxPlayers"
#define NAME_TEXT "Name"
#define NUM_OF_QUESTIONS_IN_GAME_TEXT "NumOfQuestionsInGame"
#define TIME_PER_QUESTION_TEXT "TimePerQuestion"
#define STATISTICS_TEXT "Statistics"

using json = nlohmann::json;

class JsonResponsePacketSerializer {
public:
	//login
	static std::vector<unsigned char> serializeLoginResponse(const LoginResponse& loginResponse);
	static std::vector<unsigned char> serializeSignupRequest(const SignUpResponse& signUpResponse);
	//error
	static std::vector<unsigned char> serializeErrorResponse(const ErrorResponse& errorResponse);
	//rooms
	static std::vector<unsigned char> serializeLogoutResponse(const LogoutResponse& logoutResponse);
	static std::vector<unsigned char> serializeCreateRoomResponse(const CreateRoomResponse& createRoomResponse);
	static std::vector<unsigned char> serializeJoinRoomResponse(const JoinRoomResponse& joinRoomResponse);
	
	static std::vector<unsigned char> serializeGetPlayersInRoomResponse(const GetPlayersInRoomResponse& getPlayersInRoomResponse);
	static std::vector<unsigned char> serializeGetRoomResponse(const GetRoomsResponse& getRoomsResponse);

	static std::vector<unsigned char> serializeHighScoreResponse(const GetHighScoreResponse& getHighScoreResponse);

	


private:
	static std::vector<unsigned char> convertJsonToBits(const json& jsonFormat, unsigned char code);
	static std::vector<unsigned char> intToBytes(int numInteger);
};