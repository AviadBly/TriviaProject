#include "RoomRequestHandlers.h"

//this might not work
RoomAdminRequestHandler::RoomAdminRequestHandler(const LoggedUser& user, const Room& room, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : RoomMemberRequestHandler(user, room, roomManager, handlerFactory)
{
	
}

bool RoomAdminRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	BYTE code = requestInfo.code;
	return code == CLOSE_ROOM_REQUEST_CODE || code == START_GAME_REQUEST_CODE || code == GET_ROOM_STATE_REQUEST_CODE;
}

RequestResult RoomAdminRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	RequestResult requestResult;

	try {
		switch (requestInfo.code) {
		case CLOSE_ROOM_REQUEST_CODE:
			requestResult = closeRoom();
			delete this;
			break;
		case START_GAME_REQUEST_CODE:
			requestResult = startGame();
			delete this;
			break;
		case GET_ROOM_STATE_REQUEST_CODE:
			requestResult = getRoomState();
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


RequestResult RoomAdminRequestHandler::startGame()
{

	RequestResult requestResult;
	StartRoomResponse StartRoomResponse;
	m_room.setIsActive(true); 
	m_roomManager.setRoomActive(m_room.getData().id);
	StartRoomResponse.status = StartRoomResponse.status_ok;
	this->m_roomManager.deleteRoom(m_room.getData().id);

	requestResult.buffer = JsonResponsePacketSerializer::serializeStartGameResponse(StartRoomResponse);
		
	requestResult.newHandler = m_handlerFactory.createGameRequestHandler(m_room, m_user, true);

	return requestResult;
}

RequestResult RoomAdminRequestHandler::closeRoom()
{
	RequestResult requestResult;
	CloseRoomResponse closeRoomResponse;
		
	requestResult = leaveRoom();		//maybe add this later to leave the room
	this->m_roomManager.deleteRoom(m_room.getData().id);

	closeRoomResponse.status = closeRoomResponse.status_ok;

	requestResult.buffer = JsonResponsePacketSerializer::serializeCloseRoomResponse(closeRoomResponse);
	
	return requestResult;
}
