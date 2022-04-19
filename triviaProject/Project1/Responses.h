#pragma once
#include <string>
#include <vector>
#include "Room.h"

struct Response {
	unsigned int status;
	const unsigned int status_ok = 2;
	const unsigned int status_error = 5;
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
	std::vector<Room> rooms;
};

struct GetPlayersInRoomResponse {
	std::vector<std::string> players;
};

struct GetHighScoreResponse : public Response {
	std::vector<std::string> statistics;
};

struct GetPersonalStatsResponse : public Response {
	std::vector<std::string> statistics;
};

struct JoinRoomResponse : public Response {

};

struct CreateRoomResponse : public Response {

};