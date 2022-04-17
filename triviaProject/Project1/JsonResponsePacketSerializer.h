#pragma once
<<<<<<< HEAD
#include "Requests.h"
=======
<<<<<<< HEAD
#include "Login_SignUp_Requests.h"
=======
#include "Requests.h"
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71
#include "Responses.h"
#include <vector>
#include "json.hpp"
#include <iostream>
#include <bitset>

using json = nlohmann::json;

class JsonResponsePacketSerializer {
public:
<<<<<<< HEAD
=======
<<<<<<< HEAD
	static std::vector<unsigned char> serializeLoginResponse(const LoginResponse& LoginRequest);
	static std::vector<unsigned char> serializeSignupRequest(const SignUpResponse& LoginRequest);
	static std::vector<unsigned char> serializeErrorResponse(const ErrorResponse& SignupRequest);
=======
>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71
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

<<<<<<< HEAD
=======
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71

private:
	static std::vector<unsigned char> convertJsonToBits(const json& jsonFormat, unsigned char code);
};