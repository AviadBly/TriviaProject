#include "Server.h"

//initialize server with data base
Server::Server(IDatabase* database) : m_handlerFactory(database), m_communicator(m_handlerFactory)
{
	this->m_database = database;
}

void Server::run()
{
	const int port = 8200;
	this->m_communicator.serve(port);
}
