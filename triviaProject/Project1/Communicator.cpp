#include "Communicator.h"



Communicator::Communicator()
{

	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(m_serverSocket);
	}
	catch (...) {}
}

void Communicator::serve(int port)
{

	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET

	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"
	
	// Connects between the socket and the configuration (port and etc..)
	if (_WINSOCK2API_::bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << port << std::endl;

	while (true)
	{
		// the main thread is only accepting clients 
		// and add then to the list of handlers
		std::cout << "Waiting for client connection request" << std::endl;
		acceptClient();
	}
}


void Communicator::acceptClient()
{

	// this accepts the client and create a specific socket from server to this client
	// the process will not continue until a client connects to the server
	SOCKET client_socket = accept(m_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Communicator and client can speak" << std::endl;

	// the function that handle the conversation with the client
	std::thread new_user(&Communicator::handleNewClient, this, client_socket);
	new_user.detach();

}

std::string Communicator::recvMsg(SOCKET socket) {

	const int maxLen = 4096;	//probobaly dont change, this is the max bytes
	const int flag = 0;
	try
	{
		char data[maxLen];

		int res = recv(socket, data, maxLen, flag);		
		if (res == INVALID_SOCKET)
		{
			std::string s = "Error while recieving from socket: ";
			s += std::to_string(socket);
			throw std::exception(s.c_str());
		}
		std::string received = "";

		for (int i = 0; i < res; i++) {
			received += data[i];
		}
				
		return received;
	
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		closesocket(socket);
	}

}

void Communicator::sendMsg(SOCKET clientSocket, std::string msg) {
	try
	{
		send(clientSocket, msg.c_str(), msg.size(), 0);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		closesocket(clientSocket);
	}
}

void Communicator::handleNewClient(SOCKET clientSocket)
{
	
	sendMsg(clientSocket, "HELLO");
	std::string userMsg = "";
	LoginRequestHandler handler;
	RequestInfo info;
	
	while (true) {
		
		userMsg = recvMsg(clientSocket);

		std::cout << "LoggedUser msg:" << userMsg.substr(5) << "\n";
					
		info.code = userMsg[0];
		std::cout << "code: " << info.code <<"\n";
		info.receivalTime = time(NULL);
		
		info.buffer = Helper::convertStringToBits(userMsg.substr(5));

		if (!handler.isRequestRelevant(info)) {
			throw std::exception("Irrelevent request");
		}

		RequestResult request = handler.handleRequest(info);
		SignUpResponse signUp = JsonRequestPacketDeserializer::deserializeSignUpRequest(request.buffer);
		std::cout << Helper::convertBitsToString(request.buffer);	

		
		break;		
	}
	
	// Closing the socket (in the level of the TCP protocol)
	closesocket(clientSocket);

}