#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <exception>
#include <iostream>
#include <string>
#include <thread>
#include <map>
#include "IRequestHandler.h"

class Communicator
{
public:
	Communicator();
	~Communicator();
	void serve(int port);

private:

	void acceptClient();
	std::string recvMsg(SOCKET socket, const int bytesNum, const int flags);
	void clientHandler(SOCKET clientSocket);

	std::map<SOCKET, IRequestHandler*> m_clients;

	SOCKET m_serverSocket;
};