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
<<<<<<< HEAD
#include "Login_SignUp_Requests.h"
=======
#include "Requests.h"
>>>>>>> 44cd3734195bd29a880b123a012af922fa0c279f
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