#pragma once
#include <string>

#include "secblock.h"
using CryptoPP::SecByteBlock;

using namespace std;

class ICryptoAlgorithm {
public:
	virtual string encrypt(string message) const = 0;
	virtual string decrypt(string encryptedMessage) const = 0;

protected:
	SecByteBlock m_privateKey;

};