#pragma comment (lib, "ws2_32.lib")
#include "WSAInitializer.h"
#include <iostream>
#include <fstream>
#include "Server.h"
#include "SqliteDataBase.h"
#include "MyException.h"

int main()
{
	
	try
	{
		WSAInitializer wsa;
		SqliteDataBase sqlDataBase;
		if (!sqlDataBase.open()) {
			throw MyException("Error with data base");
		}

		Server server(&sqlDataBase);
		server.run();

	}
	catch (const std::exception& e)
	{
		std::cout << "Exception was thrown in function: " << e.what() << std::endl;
	}
	
}
