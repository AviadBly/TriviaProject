#pragma once
#include "Requests.h"
#include "Responses.h"
#include <vector>
#include "json.hpp"
#include "Responses.h"
#include <iostream>
#include <bitset>
#include "JsonRequestPacketDeserializer.h"

#define STATUS_TEXT "Status"
#define MESSAGE_TEXT "Message"
#define PLAYERS_TEXT "Players"
#define ROOMS_TEXT "Rooms"
#define IS_ACTIVE_TEXT "IsActive"

#define MAX_PLAYERS_TEXT "MaxPlayers"
#define NAME_TEXT "Name"
#define NUM_OF_QUESTIONS_IN_GAME_TEXT "NumOfQuestionsInGame"
#define TIME_PER_QUESTION_TEXT "TimePerQuestion"
#define PERSONAL_STATISTICS_TEXT "PersonalStatistics"
#define HIGH_SCORE_PLAYERS "HighScorePlayers"
#define ID_TEXT "Id"
#define METADATA_TEXT "Metadata"
#define GAME_BEGUN_TEXT "HasGameBegun"
#define ANSWER_COUNT_TEXT "AnswerCount"
#define RESULTS_TEXT "Results"
#define ANSWERS_TEXT "Answers"
#define CORRECT_ANSWER_ID_TEXT "CorrectAnswerId"
#define CORRECT_ANSWER_COUNT_TEXT "CorrectAnswerCount"
#define WRONG_ANSWER_COUNT_TEXT "WrongAnswerCount"
#define AVERAGE_ANSWER_COUNT_TEXT "AverageAnswerCount"
#define QUESTION_STRING_TEXT "QuestionText"


using json = nlohmann::json;

class JsonResponsePacketSerializer {
public:
	//login
	static std::vector<BYTE> serializeLoginResponse(const LoginResponse& loginResponse);
	static std::vector<BYTE> serializeSignupRequest(const SignUpResponse& signUpResponse);
	//error
	static std::vector<BYTE> serializeErrorResponse(const ErrorResponse& errorResponse);
	//rooms
	static std::vector<BYTE> serializeLogoutResponse(const LogoutResponse& logoutResponse);
	static std::vector<BYTE> serializeCreateRoomResponse(const CreateRoomResponse& createRoomResponse);
	static std::vector<BYTE> serializeJoinRoomResponse(const JoinRoomResponse& joinRoomResponse);
	
	static std::vector<BYTE> serializeGetPlayersInRoomResponse(const GetPlayersInRoomResponse& getPlayersInRoomResponse);
	static std::vector<BYTE> serializeGetRoomResponse(const GetRoomsResponse& getRoomsResponse);

	static std::vector<BYTE> serializeHighScoreResponse(const GetHighScoreResponse& getHighScoreResponse);

	static std::vector<BYTE> serializePersonalStatisticsResponse(const GetPersonalStatsResponse& getHighScoreResponse);

	static std::vector<BYTE> serializeGetRoomStateResponse(const GetRoomStateResponse& getRoomStateRespone);

	static std::vector<BYTE> serializeStartGameResponse(const StartRoomResponse& startRoomResponse);

	static std::vector<BYTE> serializeCloseRoomResponse(const CloseRoomResponse& closeRoomResponse);

	

	
	//game
	static std::vector<BYTE> serializeLeaveRoomResponse(const LeaveRoomResponse& leaveRoomResponse);

	static std::vector<BYTE> serializeGetGameResultsResponse(const GetGameResultsResponse& getGameResultsResponse);

	static std::vector<BYTE> serializeSubmitAnswerResponse(const SubmitAnswerResponse& submitAnswerResponse);

	static std::vector<BYTE> serializeGetQuestionResponse(const GetQuestionResponse& getQuestionResponse);

	static std::vector<BYTE> serializeLeaveGameResponse(const LeaveGameResponse& leaveGameResponse);


private:
	static std::vector<BYTE> convertJsonToBits(const json& jsonFormat, BYTE code);
	
	static std::vector<BYTE> intToBytes(int numInteger);
};