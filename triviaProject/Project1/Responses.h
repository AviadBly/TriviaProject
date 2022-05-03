#pragma once
#include <string>
#include <vector>

#include "Room.h"

#define BYTE unsigned char
using namespace std;

struct Response {
	BYTE status;
	const BYTE status_ok = 2;
	const BYTE status_error = 5;
};

struct LoginResponse : public Response {
	
};

struct SignUpResponse : public Response {

};

struct ErrorResponse : public Response{
	string message;
};

struct LogoutResponse : public Response {

};

struct GetRoomsResponse : public Response {
	vector<Room> rooms;
};

struct GetPlayersInRoomResponse {
	vector<std::string> players;
};

struct GetHighScoreResponse : public Response {
	vector<string> statistics;
};

struct GetPersonalStatsResponse : public Response {
	vector<string> statistics;
};

struct JoinRoomResponse : public Response {

};

struct CreateRoomResponse : public Response {

};