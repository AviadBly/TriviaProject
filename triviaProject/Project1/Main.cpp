#pragma comment (lib, "ws2_32.lib")
#include "WSAInitializer.h"
#include <iostream>
#include <fstream>
#include "Server.h"
#include "SqliteDataBase.h"
#include "ServerException.h"

int main()
{
	
	try
	{
		WSAInitializer wsa;
		SqliteDataBase sqlDataBase;
		if (!sqlDataBase.open()) {
			throw ServerException("Error with data base", 9);
		}

		Server server(&sqlDataBase);
		server.run();

	}
	catch (const std::exception& e)
	{
		std::cout << "Exception was thrown in function: " << e.what() << std::endl;
	}
	
}
