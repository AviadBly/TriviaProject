#include "Server.h"

void Server::run()
{
	const int port = 8200;
	this->m_communicator.serve(port);
}
