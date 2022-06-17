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
#include "AesEncryptor.h"

class Communicator
{
public:
	Communicator(RequestHandlerFactory& handlerFactory);
	~Communicator();
	void serve(short port);

	static std::string recvMsg(SOCKET socket);

	static void sendMsg(SOCKET clientSocket, std::string msg);

private:
	void handleNewClient(SOCKET clientSocket);
	void acceptClient();
	
	static SecByteBlock diffiHellmanKeyExchange(SOCKET socket);

	string encryptMessageData(const string& message, AesEncryptor& encryptor);

	//SecByteBlock getKeyForSecureConnection(SOCKET socket);

	//SecByteBlock m_key;

	RequestHandlerFactory& m_handlerFactory;
	std::map<SOCKET, IRequestHandler*> m_clients;
	SOCKET m_serverSocket;


};