#pragma once
#include <string>
<<<<<<< HEAD
=======
#include <vector>
#include "Room.h"
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f

struct Response {
	unsigned int status;
	const unsigned int status_ok = 2;
	const unsigned int status_error = 5;
<<<<<<< HEAD
};

struct LoginResponse : public Response {
	
};

struct SignUpResponse : public Response {

};

struct ErrorResponse {
	std::string message;
};
=======
};

struct LoginResponse : public Response {
	
};

struct SignUpResponse : public Response {

};

struct ErrorResponse {
	std::string message;
};

struct LogoutResponse : public Response {

};

struct GetRoomsResponse : public Response {
	std::vector<std::string> rooms;
};

struct GetPlayersInRoomResponse {
	std::vector<std::string> players;
};

struct getHighScoreResponse : public Response {
	std::vector<std::string> statistics;
};

struct getPersonalStatsResponse : public Response {
	std::vector<std::string> statistics;
};

struct JoinRoomResponse : public Response {

};

struct CreateRoomResponse : public Response {

};
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
