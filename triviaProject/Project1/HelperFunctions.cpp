#include "HelperFunctions.h"

std::vector<BYTE> Helper::convertStringToBits(const std::string& str)
{
	std::vector<BYTE> bits;
	for (unsigned int i = 0; i < str.length(); i++) {
		bits.push_back(str[i]);
	}

	return bits;
}

std::string Helper::convertBitsToString(const std::vector<BYTE> bits)
{
	std::string str = "";
	
	for (unsigned int i = 0; i < bits.size(); i++) {
		str += bits[i];
	}

	return str;
}