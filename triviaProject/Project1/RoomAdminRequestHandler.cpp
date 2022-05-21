#include "RoomRequestHandlers.h"

//this might not work
RoomAdminRequestHandler::RoomAdminRequestHandler(Room room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : RoomMemberRequestHandler(room, user, roomManager, handlerFactory)
{
	
}

bool RoomAdminRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
	BYTE code = requestInfo.code;
	return code == CLOSE_ROOM_REQUEST_CODE || code == START_GAME_REQUEST_CODE || code == GET_ROOM_STATE_REQUEST_CODE;
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult requestResult;

	try {
		switch (requestInfo.code) {
		case CLOSE_ROOM_REQUEST_CODE:
			requestResult = closeRoom(requestInfo);
			break;
		case START_GAME_REQUEST_CODE:
			requestResult = startGame(requestInfo);;
			break;
		case GET_ROOM_STATE_REQUEST_CODE:
			requestResult = getRoomState(requestInfo);
			break;
		}

	}
	catch (const std::exception& e) {
		std::cout << e.what() << "\n";
	}

	if (requestResult.newHandler == nullptr) {
		requestResult.newHandler = this;
	}

	return requestResult;
}


RequestResult RoomAdminRequestHandler::startGame(RequestInfo requestInfo)
{

	RequestResult requestResult;
	StartRoomResponse StartRoomResponse;
	m_room.setIsActive(true); 
	this->m_roomManager.setRoomActive(m_room.getData().id);
	StartRoomResponse.status = StartRoomResponse.status_ok;

	requestResult.buffer = JsonResponsePacketSerializer::serializeStartGameResponse(StartRoomResponse);

	return requestResult;
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo requestInfo)
{
	RequestResult requestResult;
	CloseRoomResponse closeRoomResponse;
	

	this->m_roomManager.deleteRoom(m_room.getData().id);
	requestResult = leaveRoom(requestInfo);		//maybe add this later to leave the room
	
	closeRoomResponse.status = closeRoomResponse.status_ok;

	requestResult.buffer = JsonResponsePacketSerializer::serializeCloseGameResponse(closeRoomResponse);
	
	return requestResult;
}
