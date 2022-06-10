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

class KeyExchange {

	string getKey(SOCKET socket);

};
