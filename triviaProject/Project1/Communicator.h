#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <exception>
#include <iostream>
#include <string>
#include <thread>
#include <map>
#include <ctime>
#include <chrono>
#include "Requests.h"
#include "JsonRequestPacketDeserializer.h"
#include "HelperFunctions.h"
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"
#include "ServerException.h"
#include "KeyExchangeManager.h"

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


class Communicator
{
public:
	Communicator(RequestHandlerFactory& handlerFactory);
	~Communicator();
	void serve(int port);

	static std::string recvMsg(SOCKET socket);

	static void sendMsg(SOCKET clientSocket, std::string msg);

private:
	void handleNewClient(SOCKET clientSocket);
	void acceptClient();
	
	
	static SecByteBlock diffiHellmanKeyExchange(SOCKET socket);

	//SecByteBlock getKeyForSecureConnection(SOCKET socket);

	//SecByteBlock m_key;

	RequestHandlerFactory& m_handlerFactory;
	std::map<SOCKET, IRequestHandler*> m_clients;
	SOCKET m_serverSocket;


};