#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
	this->m_room = room;
	this->m_user = user;
}

bool RoomAdminRequestHandler::isRequestRelevant() const
{
	return false;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo requestInfo)
{
	return RequestResult();
}
