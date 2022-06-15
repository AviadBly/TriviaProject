#pragma once
#include <string>

#include "secblock.h"
using CryptoPP::SecByteBlock;

using namespace std;

class ICryptoAlgorithm {
public:
	virtual string encrypt(const string& message) const = 0;
	virtual string decrypt(const string& encryptedMessage) const = 0;

protected:
	SecByteBlock m_privateKey;

};