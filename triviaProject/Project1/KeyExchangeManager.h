#pragma once
#include "Communicator.h"
#include <iostream>
#include <string>


#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

#include <string>
using std::string;

#include <stdexcept>
using std::runtime_error;

#include <cstdlib>
using std::exit;

#include "osrng.h"
using CryptoPP::AutoSeededRandomPool;
using CryptoPP::AutoSeededX917RNG;

#include "aes.h"
using CryptoPP::AES;

#include "eccrypto.h"
using CryptoPP::ECP;
using CryptoPP::ECDH;

#include "secblock.h"
using CryptoPP::SecByteBlock;

#include "oids.h"
using CryptoPP::OID;

// ASN1 is a namespace, not an object
#include "asn.h"
using namespace CryptoPP::ASN1;

#include "integer.h"
using CryptoPP::Integer;

#include "nbtheory.h"

#include "dh.h"


class KeyExchange {

public:
	
	SecByteBlock getKey(SOCKET socket);

private:
	void initializeParameters();
	void sendParameters(SOCKET socket);
	void getClientPublicKey(SOCKET socket);


	void UnsignedIntegerToByteBlock(const Integer& x, SecByteBlock& bytes);
	void printByteArr(BYTE arr[], int len, string msg);
	string returnMsgFromBytes(SecByteBlock bytes, BYTE code);

	SecByteBlock getPublicKey() const;
	SecByteBlock getPrivateKey() const;
	SecByteBlock getClientPublicKey() const;

	CryptoPP::DH m_DHC; //short for - diffie-hellman-connection
	SecByteBlock m_publicKey;
	SecByteBlock m_privateKey;
	SecByteBlock m_clientPublicKey;
};
