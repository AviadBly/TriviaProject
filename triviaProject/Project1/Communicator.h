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
#include "Login_SignUp_Requests.h"
#include "JsonRequestPacketDeserializer.h"
#include "HelperFunctions.h"
#include "IRequestHandler.h"
#include "LoginRequestHandler.h"

class Communicator
{
public:
	Communicator(RequestHandlerFactory& handlerFactory);
	~Communicator();
	void serve(int port);

private:
	void handleNewClient(SOCKET clientSocket);
	void acceptClient();
	std::string recvMsg(SOCKET socket);

	void sendMsg(SOCKET clientSocket, std::string msg);
	
	RequestHandlerFactory& m_handlerFactory;
	std::map<SOCKET, IRequestHandler*> m_clients;
	SOCKET m_serverSocket;
};