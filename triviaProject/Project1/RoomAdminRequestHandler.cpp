#include "RoomRequestHandlers.h"


//RELEVANT FOR ALL THE HANDLER FILES: the handler receive a request from the client, deserializes the data using the deserialization functions
//and then sends the data to the  managers. the managers usually will access the database and apply the changes accordingly.

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
	
	
	requestResult.buffer = JsonResponsePacketSerializer::serializeStartGameResponse(StartRoomResponse);
		
	requestResult.newHandler = m_handlerFactory.createGameRequestHandler(m_roomManager.getSingleRoom(recentRoomId), m_user, true);
	
	//if you are the only user, delete the room
	if (--m_roomManager.getSingleRoom(recentRoomId).numberOfPlayersActive == 0) {
		m_roomManager.deleteRoom(recentRoomId);
	}

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
