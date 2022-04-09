#pragma comment (lib, "ws2_32.lib")
#include "WSAInitializer.h"
#include <iostream>
#include <fstream>
#include "Server.h"

int main()
{
	
	try
	{
		WSAInitializer wsa;

		Server server;
		server.serve(8200);

	}
	catch (const std::exception& e)
	{
		std::cout << "Exception was thrown in function: " << e.what() << std::endl;
	}
	
}
