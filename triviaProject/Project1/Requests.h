#pragma once
#include <string>

#define SIGN_UP_REQUEST_CODE 10
#define LOGIN_REQUEST_CODE 20
#define ERROR_RESPONSE_CODE 50
#define LOGOUT_REQUEST_CODE 21

#define CREATE_ROOM_CODE 30
#define GET_ROOM_REQUEST 31
#define GET_PLAYERS_IN_ROOM_REQUEST_CODE 32
#define JOIN_ROOM_REQUEST_CODE 33
#define GET_PERSONAL_STATISTICS_REQUEST_CODE 34 
#define GET_HIGH_SCORES_REQUEST_CODE 35


#define CLOSE_ROOM_REQUEST_CODE 41
#define START_ROOM_REQUEST_CODE 42 
#define LEAVE_ROOM_REQUEST_CODE 43
#define GET_ROOM_STATE_REQUEST_CODE 45




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