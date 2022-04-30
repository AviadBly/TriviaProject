#pragma once
#include <thread>
#include "Communicator.h"
//#include "HandleRequestFactory.h"

class Server {
	
public:
	Server(IDatabase* database);
	void run();

private:
	Communicator m_communicator;
	IDatabase* m_database;
	RequestHandlerFactory m_handlerFactory;
};