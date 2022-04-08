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
#include "HelperFunctions.h"
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"

class Communicator
{
public:
	Communicator();
	~Communicator();
	void serve(int port);

private:

	void acceptClient();
	std::string recvMsg(SOCKET socket, const int bytesNum, const int flags);
	void handleNewClient(SOCKET clientSocket);


	std::map<SOCKET, IRequestHandler*> m_clients;

	SOCKET m_serverSocket;
};