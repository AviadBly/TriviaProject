#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(Room room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
	this->m_room = room;
	this->m_user = user;
}

bool RoomMemberRequestHandler::isRequestRelevant() const
{
	return false;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo requestInfo)
{
	return RequestResult();
}
