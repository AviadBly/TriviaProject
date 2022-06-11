#include "Communicator.h"


Communicator::Communicator(RequestHandlerFactory& handlerFactory) : m_handlerFactory(handlerFactory)
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

	RoomData d;
	d.id = 1;
	d.maxPlayers = 5;
	d.name = "firstR";
	d.numOfQuestionsInGame = 6;
	d.timePerQuestion = 12;

	this->m_handlerFactory.getRoomManager().createRoom(LoggedUser("sha", "123"), d);
	d.id = 2;
	d.name = "secondRoom";
	d.numOfQuestionsInGame = 11;
	d.timePerQuestion = 20;
	this->m_handlerFactory.getRoomManager().createRoom(LoggedUser("gal", "568"), d);

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

//turns 4 bytes to an integer
int bytesToInt(BYTE bytes[]) {

	int num = int((unsigned char)(bytes[0]) << 24 |
		(unsigned char)(bytes[1]) << 16 |
		(unsigned char)(bytes[2]) << 8 |
		(unsigned char)(bytes[3]));

	return num;
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
		BYTE lenBytes[4];

		received += data[0];
		for (int i = 0; i < 4; i++) {
			lenBytes[i] = data[i + 1];
			received += data[i + 1];
		}

		int dataLen = bytesToInt(lenBytes);

 		for (int i = 0; i < dataLen; i++) {
			received += data[i + 5];
		}
				
		return received;
	
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		closesocket(socket);
		return "";
	}

	
}
//send string msg
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

void printByteArr(BYTE arr[], int len) {
	for (int i = 0; i < len; i++) {
		cout << (int)arr[i] << ", ";
	}
	cout << "\n\n";
}

SecByteBlock Communicator::getKeyForSecureConnection(SOCKET socket)
{

	OID CURVE = brainpoolP160r1();
	AutoSeededRandomPool rng;

	ECDH < ECP >::Domain dhA(CURVE);
	
	
	// Don't worry about point compression. Its amazing that Certicom got
	// a patent for solving an algebraic equation....
	// dhA.AccessGroupParameters().SetPointCompression(true);
	// dhB.AccessGroupParameters().SetPointCompression(true);
	cout << "length:" << dhA.AgreedValueLength() << "\n";

	//generates the public and private keys, which are byte array
	SecByteBlock privA(dhA.PrivateKeyLength()), pubA(dhA.PublicKeyLength());

	dhA.GenerateKeyPair(rng, privA, pubA);

	//cout << "public: " << pubA.data() << "\nprivate: " << privA.data() << "\b";
	auto g = dhA.GetGenerator();
	auto h = dhA.GetGroupParameters();
	//auto f = dhA.GetMaterial();
	//CryptoParameters y = dhA.GetCryptoParameters();

	cout << "Private: ";
	printByteArr(privA, dhA.PrivateKeyLength());
	cout << "Public: ";
	printByteArr(pubA, dhA.PublicKeyLength());

	std::string userMsg = recvMsg(socket);

	if (userMsg[0] != SECURE_CONNECTION_REQUEST) {
		throw ("NO SECURE CONNECTION!");
	}

	vector<BYTE> byteData = Helper::convertStringToBits(userMsg.substr(5));
	
	BYTE* clientPublicKey = new BYTE[byteData.size()];

	int i = 0;
	for (auto& b : byteData) {
		clientPublicKey[i] = b;
	}
	cout << "Client public: ";
	printByteArr(clientPublicKey, byteData.size());

	GetPublicKeyRequest getPublicKeyRequest = JsonRequestPacketDeserializer::deserializeGetPublicKeyRequest(byteData);
	
	if (byteData.size() != dhA.AgreedValueLength()) {
		throw ("LENGTH ERROR");
	}

	SecByteBlock sharedA(dhA.AgreedValueLength()); //this will be the shared key

	const bool wasAgreed = dhA.Agree(sharedA, privA, clientPublicKey);

	StartSecureConnectionResponse startResponse;

	for (int i = 0; i < pubA.size(); i++) {
		startResponse.serverPublicKey.push_back(pubA[i]);
	}
	vector<BYTE> goingMsg = JsonResponsePacketSerializer::serializeStartSecureConnectionResponse(startResponse);
	
	sendMsg(socket, Helper::convertBitsToString(goingMsg));
	
	return sharedA;
}



void Communicator::handleNewClient(SOCKET clientSocket)
{
	
	m_key = getKeyForSecureConnection(clientSocket);

	std::string userMsg = "";
	
	
	RequestInfo info;
	RequestResult request;

	//first create the login requestHandler
	request.newHandler = this->m_handlerFactory.createLoginRequestHandler();
	
	
	try {
		while (true) {

			userMsg = recvMsg(clientSocket);

			std::cout << "LoggedUser msg:" << userMsg.substr(5) << "\n";

			info.code = userMsg[0];
			std::cout << "code: " << info.code << "\n";
			info.receivalTime = time(NULL);
			
			info.buffer = Helper::convertStringToBits(userMsg.substr(5));


			if (!request.newHandler->isRequestRelevant(info)) {
				std::cout << "Irrelevent request\n";
				continue;
			}
			
			request = request.newHandler->handleRequest(info);
			this->m_clients[clientSocket] = request.newHandler;
			
			sendMsg(clientSocket, Helper::convertBitsToString(request.buffer));
			
		}
	}
	catch (const ServerException& serverException) {
		ErrorResponse er(serverException);
		//sends an error msg
		sendMsg(clientSocket, Helper::convertBitsToString(JsonResponsePacketSerializer::serializeErrorResponse(er)));
		closesocket(clientSocket);
	}
	catch(std::exception e) {
		// Closing the socket (in the level of the TCP protocol)
		closesocket(clientSocket);
	}
	
	
	
	

}