#pragma once

#include <WinSock2.h>
#include <Windows.h>
#include <exception>
#include <iostream>
#include <string>
#include <thread>

class Server
{
public:
	Server();
	~Server();
	void serve(int port);

private:

	void acceptClient();
	std::string recvMsg(SOCKET socket);
	void clientHandler(SOCKET clientSocket);

	SOCKET _serverSocket;
};