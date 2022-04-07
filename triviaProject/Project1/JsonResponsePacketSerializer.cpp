#include "JsonResponsePacketSerializer.h"

using namespace nlohmann;
std::vector<unsigned char> JsonResponePacketSerializer::serializeLoginResponse(const LoginResponse& loginResponse)
{
	//init json
	json jsonResponse;
	jsonResponse["status"] = loginResponse.status;
	jsonResponse["username"] = loginResponse.username;
	jsonResponse["password"] = loginResponse.password;

	convertJsonToBits(jsonResponse);
}

std::vector<unsigned char> JsonResponePacketSerializer::serializeSignUpResponse(const SignUpResponse& signUpResponse)
{
	//init json
	json jsonResponse;
	jsonResponse["status"] = signUpResponse.status;
	jsonResponse["username"] = signUpResponse.username;
	jsonResponse["password"] = signUpResponse.password;
	jsonResponse["email"] = signUpResponse.email;

	convertJsonToBits(jsonResponse);
}

std::vector<unsigned char> JsonResponePacketSerializer::serializeErrorResponse(const ErrorResponse& errorResponse)
{
	//init json
	json jsonResponse;
	jsonResponse["status"] = errorResponse.status;
	jsonResponse["message"] = errorResponse.message;
	
	std::vector<unsigned char> jsonBits = convertJsonToBits(jsonResponse);
	jsonBits.push_back();
	return jsonBits;
}

std::vector<unsigned char> JsonResponePacketSerializer::convertJsonToBits(const json& jsonFormat)
{
	//convert the json format to string
	std::string jsonString = jsonFormat.dump();
	std::vector<unsigned char> jsonBits;

	std::cout << jsonString << "\n";
	//convert the json string to vector bits
	for (int i = 0; i < jsonString.length(); i++) {
		jsonBits.push_back(jsonString[i]);
	}

	//add the length of the data 
	unsigned int length = jsonBits.size();
	std::string binaryStringLength = std::bitset<8>(32).to_string();
	
	for (int i = 0; i < jsonString.length(); i++) {
		jsonBits.push_back(binaryStringLength[i]);
	}

	return jsonBits;
}