#include "RoomAdminRequestHandler.h"

//this might not work
RoomAdminRequestHandler::RoomAdminRequestHandler(Room room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : RoomAdminRequestHandler(room, user, roomManager, handlerFactory)
{
	
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
	BYTE code = requestInfo.code;
	return code == CLOSE_ROOM_REQUEST_CODE || code == START_ROOM_REQUEST_CODE || code == GET_ROOM_STATE_REQUEST_CODE;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo requestInfo)
{
	return RequestResult();
}

