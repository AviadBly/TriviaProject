#pragma once
#include "ICryptoAlgorithm.h"
#include "aes.h"
#include "sha.h"
#include <osrng.h>
#include <rpcndr.h>

#include "modes.h"
using CryptoPP::CFB_Mode;

using CryptoPP::AES;
using CryptoPP::SHA256;

class AesEncryptor : public ICryptoAlgorithm {

public:
	AesEncryptor(const SecByteBlock& sharedSecretKey);
	virtual string encrypt(const string& message) const;
	virtual string decrypt(const string& encryptedMessage) const;

private:
	const int aesKeyLength = SHA256::DIGESTSIZE; // 32 bytes = 256 bit key
	const int defBlockSize = AES::BLOCKSIZE;


};