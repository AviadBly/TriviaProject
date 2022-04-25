#pragma once
#include <string>

#define SIGN_UP_REQUEST_CODE 10
#define LOGIN_REQUEST_CODE 20
#define ERROR_RESPONSE_CODE 50

#define CREATE_ROOM_CODE 30
#define GET_ROOM_REQUEST 31
#define GET_PLAYERS_IN_ROOM_REQUEST_CODE 32
#define JOIN_ROOM_REQUEST_CODE 33
#define GET_STATISTICS_REQUEST_CODE 34 
#define LOGOUT_REQUEST_CODE 35

struct LoginRequest {
	std::string username;
	std::string password;
};


struct SignupRequest : public LoginRequest {
	std::string email;
};

struct GetPlayersInRoomRequest {
	unsigned int roomId;
};

struct JoinRoomRequest {
	unsigned int roomId;
};

struct CreateRoomRequest {
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};