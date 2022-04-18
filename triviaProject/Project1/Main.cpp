#pragma comment (lib, "ws2_32.lib")
#include "WSAInitializer.h"
#include <iostream>
#include <fstream>
#include "Server.h"
#include "SqliteDataBase.h"
#include "MyException.h"

int main()
{
	/*RoomData rm;
	GetRoomsResponse r;
	rm.name = "one";
	r.rooms.push_back(rm);
	rm.name = "two";
	r.rooms.push_back(rm);
	JsonResponsePacketSerializer::serializeGetRoomResponse(r);*/
	/*try
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
	}*/
	
}
