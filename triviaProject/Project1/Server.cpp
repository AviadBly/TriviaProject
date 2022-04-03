#include "Server.h"


Server::Server()
{

	// this server use TCP. that why SOCK_STREAM & IPPROTO_TCP
	_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Server::~Server()
{
	try
	{
		// the only use of the destructor should be for freeing 
		// resources that was allocated in the constructor
		closesocket(_serverSocket);
	}
	catch (...) {}
}

void Server::serve(int port)
{

	struct sockaddr_in sa = { 0 };

	sa.sin_port = htons(port); // port that server will listen for
	sa.sin_family = AF_INET;   // must be AF_INET

	sa.sin_addr.s_addr = INADDR_ANY;    // when there are few ip's for the machine. We will use always "INADDR_ANY"
	
	// Connects between the socket and the configuration (port and etc..)
	if (bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
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


void Server::acceptClient()
{

	// this accepts the client and create a specific socket from server to this client
	// the process will not continue until a client connects to the server
	SOCKET client_socket = accept(_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);

	std::cout << "Client accepted. Server and client can speak" << std::endl;
	// the function that handle the conversation with the client
	clientHandler(client_socket);
}

std::string Server::recvMsg(SOCKET socket) {

	const int maxLen = 4096;
	std::string msg = "";
	try
	{
		char m[maxLen];
		recv(socket, m, maxLen, 0);
		
		for (int i = 0; i < maxLen; i++) {
			if (m[i] == 0) {
				break;
			}
			msg += m[i];
		}	
		return msg;
	
	}
	catch (const std::exception& e)
	{
		closesocket(socket);
	}

}

void Server::clientHandler(SOCKET clientSocket)
{
	std::string s = "HELLO";
	send(clientSocket, s.c_str(), s.size(), 0);  // last parameter: flag. for us will be 0.
	std::string userMsg = "";
	while (true) {
		
		userMsg = recvMsg(clientSocket);

		std::cout << "User msg:" << userMsg << "\n";
		if (userMsg == "Exit") {
			s = "Bye";
			send(clientSocket, s.c_str(), s.size(), 0);
			break;
		}


		// Closing the socket (in the level of the TCP protocol)
		closesocket(clientSocket);
	}
	


}