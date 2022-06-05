#include "RoomRequestHandlers.h"

RoomMemberRequestHandler::RoomMemberRequestHandler(const LoggedUser& user, Room& room, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : m_room(room), m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
	m_user = user;
	recentRoomId = room.getData().id;
}

LoginManager& RoomMemberRequestHandler::getLoginManger()
{
	return this->m_handlerFactory.getLoginManger();
}

RoomManager& RoomMemberRequestHandler::getRoomManager()
{
	return this->m_roomManager;
}

bool RoomMemberRequestHandler::isRequestRelevant(const RequestInfo& requestInfo) const
{
	BYTE code = requestInfo.code;
	return code == LEAVE_ROOM_REQUEST_CODE || code == GET_ROOM_STATE_REQUEST_CODE;
}

RequestResult RoomMemberRequestHandler::handleRequest(const RequestInfo& requestInfo)
{
	RequestResult requestResult;

	try {
		switch (requestInfo.code) {
		case LEAVE_ROOM_REQUEST_CODE:
			requestResult = leaveRoom();
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

RequestResult RoomMemberRequestHandler::leaveRoom()
{
	LeaveRoomResponse leaveRoomResponse;

	RequestResult requestResult;

	leaveRoomResponse.status = leaveRoomResponse.status_ok;

	requestResult.buffer = JsonResponsePacketSerializer::serializeLeaveRoomResponse(leaveRoomResponse);
	m_roomManager.removeUser(m_user, recentRoomId);	//no error is thrown if the room is already deleted
	
		//change back to menu handler
	requestResult.newHandler = this->m_handlerFactory.createMenuRequestHandler(m_user);
	

	return requestResult;
}


RequestResult RoomMemberRequestHandler::getRoomState()
{
	GetRoomStateResponse getRoomStateResponse;
	
	RequestResult requestResult;

	//checks if room still exist
	if (m_roomManager.doesRoomExist(recentRoomId)) {
		getRoomStateResponse.status = getRoomStateResponse.status_ok;
		RoomData roomData = this->m_room.getData();

		getRoomStateResponse.answerTimeout = roomData.timePerQuestion;	//I am not sure if its true
		getRoomStateResponse.questionCount = roomData.numOfQuestionsInGame;
		getRoomStateResponse.hasGameBegun = roomData.isActive;
		getRoomStateResponse.players = m_room.getAllUsersNames();

	}
	else {//if room doesnt exist, send the required status
		getRoomStateResponse.status = getRoomStateResponse.statusRoomNotFound;
		
	}

	
	requestResult.buffer = JsonResponsePacketSerializer::serializeGetRoomStateResponse(getRoomStateResponse);

	return requestResult;
}