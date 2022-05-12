#include "RoomRequestHandlers.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(Room room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
	this->m_room = room;
	this->m_user = user;
}

LoginManager& RoomMemberRequestHandler::getLoginManger()
{
	return this->m_handlerFactory.getLoginManger();
}

RoomManager& RoomMemberRequestHandler::getRoomManager()
{
	return this->m_roomManager;
}

bool RoomMemberRequestHandler::isRequestRelevant(RequestInfo requestInfo) const
{
	BYTE code = requestInfo.code;
	return code == LEAVE_ROOM_REQUEST_CODE || code == GET_ROOM_STATE_REQUEST_CODE;
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult requestResult;

	try {
		switch (requestInfo.code) {
		case LEAVE_ROOM_REQUEST_CODE:
			requestResult = leaveRoom(requestInfo);
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

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo requestInfo)
{
	LeaveRoomResponse leaveRoomResponse;

	RequestResult requestResult;

	leaveRoomResponse.status = leaveRoomResponse.status_ok;

	requestResult.buffer = JsonResponsePacketSerializer::serializeLeaveGameResponse(leaveRoomResponse);

	requestResult.newHandler = this->m_handlerFactory.createMenuRequestHandler(this->m_user);	//change back to menu handler
	
	delete this;

	return requestResult;
}


RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo requestInfo)
{
	GetRoomStateResponse getRoomStateResponse;
	
	RequestResult requestResult;
	//if room exist
	if (m_roomManager.getRoomState(m_room.getData().id)) {
		getRoomStateResponse.status = getRoomStateResponse.status_ok;
		RoomData roomData = this->m_room.getData();

		getRoomStateResponse.answerTimeout = roomData.timePerQuestion;	//I am not sure if its true
		getRoomStateResponse.questionCount = roomData.numOfQuestionsInGame;
		getRoomStateResponse.hasGameBegun = roomData.isActive;
		getRoomStateResponse.players = m_room.getAllUsers();

	}
	else {//if room doesnt exist
		getRoomStateResponse.status = getRoomStateResponse.statusRoomNotFound;

		delete this;
	}

	
	requestResult.buffer = JsonResponsePacketSerializer::serializeGetRoomStateResponse(getRoomStateResponse);

	return requestResult;
}