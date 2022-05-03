#pragma once

#include <vector>
#include <string>
#include "Responses.h"

class Helper {
public:
	static std::vector<BYTE> convertStringToBits(const std::string& str);
	static std::string convertBitsToString(const std::vector<BYTE> bits);
};