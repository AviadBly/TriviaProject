#pragma once
#include <string>
#include <vector>
#include <map>
#include "Room.h"
#include "ServerException.h"
#include "Requests.h"
typedef unsigned char BYTE;
using namespace std;

struct Response {
	unsigned int status = 0;
	const int status_ok = 2;
	const int status_error = 5;
};

struct LoginResponse : public Response {
	
};

struct SignUpResponse : public Response {

};

struct ErrorResponse : public Response{
	ErrorResponse(const ServerException& e) {
		status = e.getStatus();
		message = e.what();
	}
	ErrorResponse() {
		status = ERROR_RESPONSE_CODE;
	}
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

struct LeaveGameResponse : public Response
{

};

struct GetQuestionResponse : public Response
{
	const unsigned int noMoreQuestionStatus = 9;
	string question;
	map<unsigned int, string> answers;
};

struct SubmitAnswerResponse : public Response
{
	unsigned int correctAnswerID;
};

struct PlayerResults
{
	string username;
	unsigned int correctAnswerCount = 0;
	unsigned int wrongAnswerCount = 0;
	double averageAnswerTime = 0;
};

struct GetGameResultsResponse : public Response
{
	const unsigned int noResultsStatus = 0;
	vector<PlayerResults> results;
};

struct StartSecureConnectionResponse : public Response
{
	vector<BYTE> serverPublicKey;
};