#include "JsonResponsePacketSerializer.h"


std::vector<unsigned char> JsonResponsePacketSerializer::serializeLoginResponse(const LoginResponse& loginResponse)
{
	//init json
	json jsonResponse;
	
	jsonResponse["status"] = loginResponse.status;

	std::vector<unsigned char> jsonBits = convertJsonToBits(jsonResponse, unsigned char(LOGIN_REQUEST_CODE));
	
	return jsonBits;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeSignupRequest(const SignUpResponse& signUpResponse)
{

	//init json
	json jsonResponse;

	jsonResponse["status"] = signUpResponse.status;

	std::vector<unsigned char> jsonBits = convertJsonToBits(jsonResponse, unsigned char(SIGN_UP_REQUEST_CODE));

	return jsonBits;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeErrorResponse(const ErrorResponse& errorResponse)
{
	//init json
	json jsonResponse;
	//jsonResponse["status"] = errorResponse.status;
	jsonResponse["message"] = errorResponse.message;
	
	std::vector<unsigned char> jsonBits = convertJsonToBits(jsonResponse, unsigned char(ERROR_RESPONSE_CODE));
	
	return jsonBits;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeLogoutResponse(const LogoutResponse logoutResponse)
{
	//init json
	json jsonResponse;
	jsonResponse["status"] = logoutResponse.status;
	
	std::vector<unsigned char> jsonBits = convertJsonToBits(jsonResponse, unsigned char(logoutResponse.status_ok));

	return jsonBits;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeCreateRoomResponse(const CreateRoomResponse createRoomResponse)
{
	//init json
	json jsonResponse;
	jsonResponse["status"] = createRoomResponse.status;

	std::vector<unsigned char> jsonBits = convertJsonToBits(jsonResponse, unsigned char(createRoomResponse.status_ok));

	return jsonBits;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeJoinRoomResponse(const JoinRoomResponse joinRoomResponse)
{
	//init json
	json jsonResponse;
	jsonResponse["status"] = joinRoomResponse.status;

	std::vector<unsigned char> jsonBits = convertJsonToBits(jsonResponse, unsigned char(joinRoomResponse.status_ok));

	return jsonBits;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetPlayersInRoomResponse(const GetPlayersInRoomResponse getPlayersInRoomResponse)
{
	//init json
	json jsonResponse;
	jsonResponse["players"] = getPlayersInRoomResponse.players;
	std::cout << jsonResponse;

	std::vector<unsigned char> jsonBits = convertJsonToBits(jsonResponse, unsigned char(1));

	return jsonBits;
}

//this may not be final
std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetRoomResponse(const GetRoomsResponse getRoomsResponse)
{
	//init json
	json jsonResponse;
	jsonResponse["rooms"] = getRoomsResponse.rooms;
	std::cout << jsonResponse;

	std::vector<unsigned char> jsonBits = convertJsonToBits(jsonResponse, unsigned char(1));

	return jsonBits;
}

//this may not be final
std::vector<unsigned char> JsonResponsePacketSerializer::serializeHighScoreResponse(const getHighScoreResponse getHighScoreResponse)
{
	//init json
	json jsonResponse;
	jsonResponse["statistics"] = getHighScoreResponse.statistics;
	std::cout << jsonResponse;

	std::vector<unsigned char> jsonBits = convertJsonToBits(jsonResponse, unsigned char(1));

	return jsonBits;
}

//return a vector of bits from the given jsonFormat message + 4 bits of the length of the message + the code
std::vector<unsigned char> JsonResponsePacketSerializer::convertJsonToBits(const json& jsonFormat, unsigned char code)
{


	//convert the json format to string
	std::string jsonString = jsonFormat.dump();
	std::vector<unsigned char> jsonBits;

	//add the msg code
	jsonBits.push_back(code);

	//add the length of the data 
	unsigned int length = jsonString.length();

	std::string binaryStringLength = std::bitset<32>(length).to_string();
	for (unsigned int i = 0; i < binaryStringLength.length(); i++) {
		jsonBits.push_back(binaryStringLength[i]);
	}

	std::cout << jsonString << "\n";
	//add the json string
	for (unsigned int i = 0; i < jsonString.length(); i++) {
		jsonBits.push_back(jsonString[i]);
	}

	return jsonBits;
}
