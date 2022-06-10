#pragma once
#include <string>

using namespace std;

class ICryptoAlgorithm {
public:
	virtual string encrypt(string data) = 0;
	virtual string decrypt(string data) = 0;
};