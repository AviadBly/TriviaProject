#pragma once
#include <vector>
#include <iostream>
#include <bitset>
#include "json.hpp"
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

using json = nlohmann::json;

class JsonRequestPacketDeserializer {
public:
<<<<<<< HEAD
=======
<<<<<<< HEAD
	static LoginRequest deserializeLoginResponse(std::vector<char unsigned> jsonResponseBits);
	static SignupRequest deserializeSignUpResponse(std::vector<char unsigned> jsonResponseBits);
	static ErrorResponse deserializeErrorResponse(std::vector<char unsigned> jsonResponseBits);

=======
>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71
	//login
	static LoginRequest deserializeLoginRequest(std::vector<char unsigned> jsonRequestBits);
	static SignupRequest deserializeSignUpRequest(std::vector<char unsigned> jsonRequestBits);
	//error
	//static ErrorRequest deserializeErrorRequest(std::vector<char unsigned> jsonRequestBits);
	
	//rooms
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector<char unsigned> jsonRequestBits);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector<char unsigned> jsonRequestBits);
	static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(std::vector<char unsigned> jsonRequestBits);
	
<<<<<<< HEAD
=======
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
>>>>>>> 928e187a8540f806632ae1f6c84f9a7604372e71
private:
	static json getJsonFromBits(std::vector<char unsigned> jsonRequestBits);
};