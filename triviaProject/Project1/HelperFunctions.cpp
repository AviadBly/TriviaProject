#include "HelperFunctions.h"

std::vector<unsigned char> Helper::convertStringToBits(const std::string& str)
{
	std::vector<unsigned char> bits;
	for (int i = 0; i < str.length(); i++) {
		bits.push_back(str[i]);
	}

	return bits;
}