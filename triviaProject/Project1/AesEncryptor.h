#pragma once
#include "ICryptoAlgorithm.h"
#include "aes.h"
#include "sha.h"
#include <osrng.h>

#include "filters.h"

#include "modes.h"
using CryptoPP::CFB_Mode;
using CryptoPP::CBC_Mode;

using CryptoPP::AES;
using CryptoPP::SHA256;

class AesEncryptor : public ICryptoAlgorithm {

public:
	
	AesEncryptor(const SecByteBlock& sharedSecretKey);

	virtual string encrypt(string message);
	virtual string decrypt(string encryptedMessage);

private:
	const int aesKeyLength = SHA256::DIGESTSIZE; // 32 bytes = 256 bit key
	const int defBlockSize = AES::BLOCKSIZE;

	
	SecByteBlock m_iv;
	//CryptoPP::byte m_iv[AES::BLOCKSIZE];
	void updateInitializationVector(SecByteBlock arr);
};