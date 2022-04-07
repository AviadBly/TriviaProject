#include "JsonResponsePacketSerializer.h"

using namespace nlohmann;
std::vector<unsigned char> JsonResponePacketSerializer::serializeLoginResponse(const LoginResponse& loginResponse)
{
	//init json
	json jsonResponse;
	jsonResponse["status"] = loginResponse.status;
	jsonResponse["username"] = loginResponse.username;
	jsonResponse["password"] = loginResponse.password;

	std::vector<unsigned char> jsonBits = convertJsonToBits(jsonResponse);
	jsonBits.push_back(char(LOGIN_RESPONSE_CODE));
	return jsonBits;
}

std::vector<unsigned char> JsonResponePacketSerializer::serializeSignUpResponse(const SignUpResponse& signUpResponse)
{

	//init json
	json jsonResponse;
	jsonResponse["status"] = signUpResponse.status;
	jsonResponse["username"] = signUpResponse.username;
	jsonResponse["password"] = signUpResponse.password;
	jsonResponse["email"] = signUpResponse.email;

	std::vector<unsigned char> jsonBits = convertJsonToBits(jsonResponse);
	//add the response code
	jsonBits.push_back(char(SIGN_RESPONSE_CODE));

	return jsonBits;
}

std::vector<unsigned char> JsonResponePacketSerializer::serializeErrorResponse(const ErrorResponse& errorResponse)
{
	//init json
	json jsonResponse;
	jsonResponse["status"] = errorResponse.status;
	jsonResponse["message"] = errorResponse.message;
	
	std::vector<unsigned char> jsonBits = convertJsonToBits(jsonResponse);
	jsonBits.push_back(char(ERROR_RESPONSE_CODE));
	return jsonBits;
}

//return a vector of bits from the given jsonFormat message + 4 bits of the length of the message
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
