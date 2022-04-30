#include "HelperFunctions.h"

std::vector<unsigned char> Helper::convertStringToBits(const std::string& str)
{
	std::vector<unsigned char> bits;
	for (int i = 0; i < str.length(); i++) {
		bits.push_back(str[i]);
	}

	return bits;
}

std::string Helper::convertBitsToString(const std::vector<unsigned char> bits)
{
	std::string str = "";
	
	for (int i = 0; i < bits.size(); i++) {
		str += bits[i];
	}

	return str;
}