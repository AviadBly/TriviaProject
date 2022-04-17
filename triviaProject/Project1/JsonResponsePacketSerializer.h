#pragma once
<<<<<<< HEAD
#include "Login_SignUp_Requests.h"
=======
#include "Requests.h"
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
#include "Responses.h"
#include <vector>
#include "json.hpp"
#include <iostream>
#include <bitset>

using json = nlohmann::json;

class JsonResponsePacketSerializer {
public:
<<<<<<< HEAD
	static std::vector<unsigned char> serializeLoginResponse(const LoginResponse& LoginRequest);
	static std::vector<unsigned char> serializeSignupRequest(const SignUpResponse& LoginRequest);
	static std::vector<unsigned char> serializeErrorResponse(const ErrorResponse& SignupRequest);
=======
	//login
	static std::vector<unsigned char> serializeLoginResponse(const LoginResponse& loginResponse);
	static std::vector<unsigned char> serializeSignupRequest(const SignUpResponse& signUpResponse);
	//error
	static std::vector<unsigned char> serializeErrorResponse(const ErrorResponse& errorResponse);
	//rooms
	static std::vector<unsigned char> serializeLogoutResponse(const LogoutResponse logoutResponse);
	static std::vector<unsigned char> serializeCreateRoomResponse(const CreateRoomResponse createRoomResponse);
	static std::vector<unsigned char> serializeJoinRoomResponse(const JoinRoomResponse joinRoomResponse);
	
	static std::vector<unsigned char> serializeGetPlayersInRoomResponse(const GetPlayersInRoomResponse getPlayersInRoomResponse);
	static std::vector<unsigned char> serializeGetRoomResponse(const GetRoomsResponse getRoomsResponse);

	static std::vector<unsigned char> serializeHighScoreResponse(const getHighScoreResponse getHighScoreResponse);

>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f

private:
	static std::vector<unsigned char> convertJsonToBits(const json& jsonFormat, unsigned char code);
};