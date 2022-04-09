#pragma once

#include <vector>
#include <string>

class Helper {
public:
	static std::vector<unsigned char> convertStringToBits(const std::string& str);
	static std::string convertBitsToString(const std::vector<unsigned char> bits);
};