#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler(Room room, LoggedUser user, RoomManager& roomManager, RequestHandlerFactory& handlerFactory) : m_roomManager(roomManager), m_handlerFactory(handlerFactory)
{
	this->m_room = room;
	this->m_user = user;
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

LoginManager& RoomAdminRequestHandler::getLoginManger()
{
	return this->m_handlerFactory.getLoginManger();
}

RoomManager& RoomAdminRequestHandler::getRoomManager()
{
	return this->m_roomManager;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo requestInfo)
{
	GetRoomStateResponse getRoomStateResponse;

	RequestResult requestResult;

	getRoomStateResponse.status = getRoomStateResponse.status_ok;
	RoomData roomData = this->m_room.getData();

	getRoomStateResponse.answerTimeout = roomData.timePerQuestion;	//I am not sure if its true
	getRoomStateResponse.questionCount = roomData.numOfQuestionsInGame;
	getRoomStateResponse.hasGameBegun = roomData.isActive;
	getRoomStateResponse.players = m_room.getAllUsers();

	requestResult.buffer = JsonResponsePacketSerializer::serializeGetRoomStateResponse(getRoomStateResponse);

	return requestResult;
}