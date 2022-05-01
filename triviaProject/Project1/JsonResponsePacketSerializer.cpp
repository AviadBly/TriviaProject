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

std::vector<unsigned char> JsonResponsePacketSerializer::serializeLogoutResponse(const LogoutResponse& logoutResponse)
{
	//init json
	json jsonResponse;
	jsonResponse["status"] = logoutResponse.status;
	
	std::vector<unsigned char> jsonBits = convertJsonToBits(jsonResponse, unsigned char(logoutResponse.status_ok));

	return jsonBits;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeCreateRoomResponse(const CreateRoomResponse& createRoomResponse)
{
	//init json
	json jsonResponse;
	jsonResponse["status"] = createRoomResponse.status;

	std::vector<unsigned char> jsonBits = convertJsonToBits(jsonResponse, unsigned char(createRoomResponse.status_ok));

	return jsonBits;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeJoinRoomResponse(const JoinRoomResponse& joinRoomResponse)
{
	//init json
	json jsonResponse;
	jsonResponse["status"] = joinRoomResponse.status;

	std::vector<unsigned char> jsonBits = convertJsonToBits(jsonResponse, unsigned char(joinRoomResponse.status_ok));

	return jsonBits;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetPlayersInRoomResponse(const GetPlayersInRoomResponse& getPlayersInRoomResponse)
{
	//init json
	json jsonResponse;
	jsonResponse["players"] = getPlayersInRoomResponse.players;
	std::cout << jsonResponse;

	std::vector<unsigned char> jsonBits = convertJsonToBits(jsonResponse, unsigned char(1));

	return jsonBits;
}

//this may not be final
std::vector<unsigned char> JsonResponsePacketSerializer::serializeGetRoomResponse(const GetRoomsResponse& getRoomsResponse)
{
	//init json
	json jsonResponse;
	for (auto i = getRoomsResponse.rooms.begin(); i != getRoomsResponse.rooms.end(); i++) {
		
		RoomData data = i->getData();
		//add the roomData to the json format
		jsonResponse["isActive"] += data.isActive;
		jsonResponse["maxPlayers"] += data.maxPlayers;
		jsonResponse["name"] += data.name;
		jsonResponse["numOfQuestionsInGame"] += data.numOfQuestionsInGame;
		jsonResponse["timePerQuestion"] += data.timePerQuestion;
		
	}
	
	
	std::cout << jsonResponse;

	std::vector<unsigned char> jsonBits = convertJsonToBits(jsonResponse, unsigned char(1));

	return jsonBits;
}

//this may not be final
std::vector<unsigned char> JsonResponsePacketSerializer::serializeHighScoreResponse(const GetHighScoreResponse& getHighScoreResponse)
{
	//init json
	json jsonResponse;
	jsonResponse["statistics"] = getHighScoreResponse.statistics;
	std::cout << jsonResponse;

	std::vector<unsigned char> jsonBits = convertJsonToBits(jsonResponse, unsigned char(1));

	return jsonBits;
}

std::vector<unsigned char> JsonResponsePacketSerializer::intToBytes(int numInteger)
{
	vector<unsigned char> arrayOfByte(4);
	for (int i = 0; i < 4; i++)
		arrayOfByte[3 - i] = (numInteger >> (i * 8));

	return arrayOfByte;
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
	std::vector<unsigned char> tempLengthBytes = intToBytes(length);

	//runs 4 times because an integer is 32 bytes and each byte is 8, so 32/8=4
	for (unsigned int i = 0; i < 4; i++) {
		jsonBits.push_back(tempLengthBytes[i]);
	}

	std::cout << jsonString << "\n";
	//add the json string
	for (unsigned int i = 0; i < jsonString.length(); i++) {
		jsonBits.push_back(jsonString[i]);
	}

	return jsonBits;
}
