#pragma once
#include <string>
#include <vector>

#include "Room.h"

#define BYTE unsigned char
using namespace std;

struct Response {
	int status;
	const int status_ok = 2;
	const int status_error = 5;
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

struct GetRoomStateResponse : public Response {
	const int statusRoomNotFound = 7;

	bool hasGameBegun;
	vector<string> players;
	unsigned int questionCount;
	unsigned int answerTimeout;

};

struct CloseRoomResponse :public Response
{

};

struct StartRoomResponse :public Response
{

};

struct LeaveRoomResponse :public Response
{

};
