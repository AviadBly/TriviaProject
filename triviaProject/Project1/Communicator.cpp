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
	if (bind(m_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
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
	clientHandler(client_socket);
}

std::string Communicator::recvMsg(SOCKET socket, const int bytesNum, const int flags) {

	
	try
	{
		if (bytesNum == 0)
		{
			return "";
		}

		char* data = new char[bytesNum + 1];
		for (int i = 0; i < bytesNum + 1; i++) {
			data[i] = '\0';
		}

		int res = recv(socket, data, bytesNum, flags);
		//end of the string

		if (res == INVALID_SOCKET)
		{
			std::string s = "Error while recieving from socket: ";
			s += std::to_string(socket);
			throw std::exception(s.c_str());
		}

		std::string received(data);
		delete[] data;

		return received;
	
	}
	catch (const std::exception& e)
	{
		closesocket(socket);
	}

}

void Communicator::clientHandler(SOCKET clientSocket)
{
	std::string s = "HELLO";
	send(clientSocket, s.c_str(), s.size(), 0);  // last parameter: flag. for us will be 0.
	std::string userMsg = "";
	const int maxLen = 4096;


	while (true) {
		
		userMsg = recvMsg(clientSocket, maxLen, 0);

		std::cout << "User msg:" << userMsg << "\n";
		if (userMsg == "Exit") {
			s = "Bye";
			send(clientSocket, s.c_str(), s.size(), 0);
			break;
		}


		
	}
	
	// Closing the socket (in the level of the TCP protocol)
	closesocket(clientSocket);

}